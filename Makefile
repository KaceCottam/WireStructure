DOCS := $(sort $(wildcard docs/*-*.md))
SRCS := $(wildcard src/*.nim)
.PHONY: default
default: build

.PHONY: all
all: build README.md

build: ${SRCS}
	nimble build

README.md: ${DOCS}
	rm -f $@
	for i in ${DOCS}; do \
		echo "[$${i#docs/}]($$i)  " >> $@; \
		cat $$i >> $@; \
		echo "___" >> $@; \
	done
