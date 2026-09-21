# Top-level Makefile — delegates the actual build to src/Makefile
# This is the "recursive make" pattern.

SUBDIR = src

.PHONY: all clean

all:
	$(MAKE) -C $(SUBDIR)

clean:
	$(MAKE) -C $(SUBDIR) clean
