.PHONY: default
default: README.md

README.md: docs/Description.md
	rm -f $@
	cat $^ >> $@
