DOCS := $(sort $(wildcard docs/*.md))
.PHONY: default
default: README.md

README.md: ${DOCS}
	rm -f $@
	for i in ${DOCS}; do \
		echo "[$${i%docs/}]($$i) " >> $@; \
		cat $$i >> $@; \
		echo "___" >> $@; \
	done
