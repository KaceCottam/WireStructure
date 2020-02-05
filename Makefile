# I use the .cxx extension for source files that define main.

CXX := g++## What compiler we are using
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Werror## Compiler flags for all operations
# Directories
SRCDIR := src## Where the source files are located
OBJDIR := build## Where the object files will be placed
BINDIR := bin## Where the finished executable will be placed
INCDIR := include## Additional include directories
# File GLOBs
SRCS      := $(wildcard ${SRCDIR}/*.cpp)
SRC_MAINS := $(wildcard ${SRCDIR}/*.cxx)
HEADS     := $(wildcard ${SRCDIR}/*.hpp)
HEADS     += $(wildcard ${SRCDIR}/*.hxx)
HEADS     += $(wildcard ${SRCDIR}/*.h)
OBJS      := ${SRCS:${SRCDIR}/%.cpp=${OBJDIR}/%.o}
# Extra Arguments
COMPILE_ARGS := ## Extra arguments for compilation
LINKING_ARGS := ## Extra arguments for linking
# Misc
EXEC          := WireStructure## The output executable for the linking process. Can also automatically use files with the .cxx extension if undefined.
EXEC_MAINS    := ${SRC_MAINS:${SRCDIR}/%.cxx=${BINDIR}/%}
DEBUG_COMMAND := ## The command to use while debugging makefile

ifeq "${DEBUG}" "1"
	COMPILE_ARGS        += -g
	LINKING_ARGS        += -g
endif
ifeq "${VERBOSE}" "1"
	COMPILE_ARGS        += -v
	LINKING_ARGS        += -v
endif

.PHONY: default
default: help

.PHONY: setup-project
setup-project: ## Sets up a project. Needs EXEC defined.

.PHONY: all
ifdef ${EXEC}
all: ${EXEC_MAINS} ## Runs all targets

setup-project:
	@echo "Did you define EXEC?"
else
all: ${BINDIR}/${EXEC}

setup-project:
	@echo "Fetching .clang-format from gist..."
	@curl -o .clang-format https://gist.githubusercontent.com/KaceCottam/957e14380e7c5e9822141c5c00ea17e4/raw/e21e1835ee0da1c27cf66c7856008265fddfd9b1/.clang-format
	@echo "...Done"
	@echo "Making source directory..."
	@mkdir -pv ${SRCDIR}
	@echo "...Done"
	@echo "Creating main..."
	@echo "int main() {}" > ${SRCDIR}/${EXEC}.cxx
	@echo "...Done"
endif

define filter-hpp
$(filter-out %.h, $(filter-out %.hpp, $(filter-out %.hxx, ${1})))
endef

.PHONY: help
help: ## Prints usage instructions
	@echo "usage: make [target] ... [<optional argument>=<value> ...]"
	@echo "----------------------------------------------------------"
	@echo "targets:"
	@awk 'BEGIN {FS=":|##"} /^[a-zA-Z].*:[^=].*##.*$$/ {printf "  %-30s %s\n", $$1, NF==2?$$2:$$3;}' $(MAKEFILE_LIST) | sort
	@echo "optional arguments:"
	@awk 'BEGIN {FS=":=|##"} /^[a-zA-Z].*[:+]=.*##.*$$/ {printf "  %-30s %s\n", $$1, $$3;}' $(MAKEFILE_LIST)  | sort

${OBJDIR}/%.o: ${SRCDIR}/%.cpp
	@mkdir -pv ${OBJDIR}
	${CXX} ${CXXFLAGS} ${COMPILE_ARGS} -c -o $@ $<

${BINDIR}/%: ${SRCDIR}/%.cxx ${OBJS} ${HEADS}
	@mkdir -pv ${BINDIR}
	${CXX} ${CXXFLAGS} ${LINKING_ARGS} -o $@ $(call filter-hpp, $^)

.PHONY: DEBUG_MAKE
DEBUG_MAKE: ## Allows for debugging of makefile
	${DEBUG_COMMAND}

.PHONY: clean
clean: ## Cleans directory to return to working state
	@echo "Cleaning Directory."
	@echo "Removing ${OBJDIR}, ${BINDIR}, ${INCDIR}..."
	@rm -rf ${OBJDIR} ${BINDIR} ${INCDIR}
	@echo "...Done"

# -------------- Testing Targets -------------- #

TESTDIR       := tests
TEST_SRCS     := $(wildcard ${TESTDIR}/*.cpp)
TEST_SRCS     += $(wildcard ${TESTDIR}/*.cxx)
TEST_BINDIR   := ${BINDIR}/${TESTDIR}## Where test binaries are placed
TEST_INCLUDES := -I${INCDIR} -I${SRCDIR}## Extra includes for tests
TEST_BINS     := ${TEST_SRCS:${TESTDIR}/%.cxx=${TEST_BINDIR}/%}

.PHONY: tests
tests: ${TEST_BINS} ## Compile all tests

.PHONY: run-tests
run-tests: tests
	for i in ${TEST_BINDIR}/*; do \
		echo "$$i" && $$i --reporter compact; \
	 	if [ $$? != 0 ]; then \
			exit $$?; \
		fi; \
	done

setup-project: setup-test-project

.PHONY: setup-test-project
setup-test-project:
	@echo "Making test directory..."
	@mkdir -pv ${TESTDIR}
	@echo "...Done"
	@echo "Making test files..."
	@echo "//PRECOMPILED HEADER FOR CATCH\n#define CATCH_CONFIG_MAIN\n#include <catch.hpp>" \
		> ${TESTDIR}/test.h
	@echo "...Done"

all: tests

${INCDIR}/catch.hpp: ## Download Catch2 Library
	@echo "Installing catch2 library to $@..."
	@mkdir -pv ${INCDIR}/
	@curl -o $@ "https://raw.githubusercontent.com/catchorg/Catch2/v2.10.2/single_include/catch2/catch.hpp" \
        1>/dev/null 3>/dev/null
	@echo "...Done"

${OBJDIR}/test.o: ${TESTDIR}/test.cpp ${INCDIR}/catch.hpp
	@mkdir -pv ${OBJDIR}
	${CXX} ${CXXFLAGS} ${COMPILE_ARGS} ${TEST_INCLUDES} -c -o $@ $<

${TEST_BINDIR}/%: ${TESTDIR}/%.cxx ${SRCDIR}/%.h ${OBJDIR}/%.o ${OBJDIR}/test.o
	@mkdir -pv ${TEST_BINDIR}
	${CXX} ${CXXFLAGS} ${COMPILE_ARGS} ${TEST_INCLUDES} -o $@ $(call filter-hpp, $^)

# ---------- Documentation ----------------- #
DOCS := $(sort $(wildcard docs/*-*.md))
README.md: ${DOCS} ## Generate a readme file based off of numbered markdown files in the docs/ folder
	@rm -vf $@
	@for i in ${DOCS}; do \
		echo "[$$i]($$i)" >> $@; \
		cat $$i >> $@; \
		echo "" >> $@; \
	done
