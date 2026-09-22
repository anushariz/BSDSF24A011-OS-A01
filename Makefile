# Top-level Makefile

SUBDIR = src
PREFIX = /usr/local

.PHONY: all clean install uninstall

all:
	$(MAKE) -C $(SUBDIR)

clean:
	$(MAKE) -C $(SUBDIR) clean

install: all
	install -d $(PREFIX)/bin
	install -m 755 bin/client $(PREFIX)/bin/client
	install -d $(PREFIX)/share/man/man1
	install -d $(PREFIX)/share/man/man3
	install -m 644 man/man1/*.1 $(PREFIX)/share/man/man1/
	install -m 644 man/man3/*.3 $(PREFIX)/share/man/man3/
	@echo "Installed client to $(PREFIX)/bin and man pages to $(PREFIX)/share/man"

uninstall:
	rm -f $(PREFIX)/bin/client
	rm -f $(PREFIX)/share/man/man1/client.1
	rm -f $(PREFIX)/share/man/man3/mystrlen.3 $(PREFIX)/share/man/man3/mystrcpy.3 \
	      $(PREFIX)/share/man/man3/mystrncpy.3 $(PREFIX)/share/man/man3/mystrcat.3 \
	      $(PREFIX)/share/man/man3/wordCount.3 $(PREFIX)/share/man/man3/mygrep.3
