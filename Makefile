# I use the .cxx extension for source files that define main.

CXX := g++## What compiler we are using
CXXFLAGS := -std=c++17## Compiler flags for all operations
# Directories
SRCDIR := src## Where the source files are located
OBJDIR := build## Where the object files will be placed
BINDIR := bin## Where the finished executable will be placed
INCDIR := include## Additional include directories
# File GLOBs
SRCS      := $(wildcard ${SRCDIR}/*.cpp)
SRC_MAINS := $(wildcard ${SRCDIR}/*.cxx)
HEADS     := $(wildcard ${SRCDIR}/*.h)
OBJS      := ${SRCS:${SRCDIR}/%.cpp=${OBJDIR}/%.o}
# Extra Arguments
COMPILE_ARGS :=## Extra arguments for compilation
LINKING_ARGS :=-pthread## Extra arguments for linking
WX_WIDGETS   :=`wx-config --cxxflags --libs std,aui`
# Misc
EXEC_MAINS    := ${SRC_MAINS:${SRCDIR}/%.cxx=${BINDIR}/%}
DEBUG         :=1## Compile with debug mode
VERBOSE       :=0## Use verbose compilation

ifeq "${DEBUG}" "1"
	CXXFLAGS += -g
endif
ifeq "${VERBOSE}" "1"
	CXXFLAGS += -v
endif

.SECONDARY:
.PHONY: default
default: help

.PHONY: all
all: ${EXEC_MAINS} ## Runs all targets

.PHONY: help
help: ## Prints usage instructions
	@echo "usage: make [target] ... [<optional argument>=<value> ...]"
	@echo "----------------------------------------------------------"
	@echo "targets:"
	@awk 'BEGIN {FS=":|##"} /^[a-zA-Z$$].*:[^=].*##.*$$/ {printf "  %-30s %s\n", $$1, NF==2?$$2:$$3;}' $(MAKEFILE_LIST) | sort
	@echo "optional arguments:"
	@awk 'BEGIN {FS=":=|##"} /^[a-zA-Z].*[:+]=.*##.*$$/ {printf "  %-30s %s\n", $$1, $$3;}' $(MAKEFILE_LIST)  | sort

${OBJDIR}/%.o: ${SRCDIR}/%.cpp
	@mkdir -pv ${OBJDIR}
	${CXX} ${CXXFLAGS} ${COMPILE_ARGS} -c -o $@ $^ ${WX_WIDGETS}

${BINDIR}/%: ${SRCDIR}/%.cxx ${OBJS} ${HEADS} ## Build an executable with a given object in src/%.cxx
	@mkdir -pv ${BINDIR}
	${CXX} ${CXXFLAGS} ${LINKING_ARGS} -o $@ $(filter-out %.h, $^) ${WX_WIDGETS}

.PHONY: clean
clean: ## Cleans directory to return to working state
	@echo "Cleaning Directory."
	@echo "Removing ${OBJDIR}, ${BINDIR}, ${INCDIR}..."
	@rm -rf ${OBJDIR} ${BINDIR} ${INCDIR}
	@echo "...Done"

# ---------- Documentation ----------------- #
DOCS := $(sort $(wildcard docs/*-*.md))
README.md: ${DOCS} ## Generate a readme file based off of numbered markdown files in the docs/ folder
	@rm -vf $@
	@for i in ${DOCS}; do \
		echo "[$$i]($$i)" >> $@; \
		cat $$i >> $@; \
		echo "" >> $@; \
	done
