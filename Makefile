CC ?= cc
CFLAGS :=
ASSETDIR ?= $(CURDIR)
INSTDIR ?= /usr/local/bin
MANDIR ?= /usr/local/share/man/man1

build: main.c format
	$(CC) *.c -o cicalc -pedantic -Wall -Werror -Wextra -O3 -march=native -lm -std=gnu99
	./cicalc --test

format:
	clang-format -i *.c
	clang-format -i *.h

test:
	./cicalc --test

install: cicalc test
	install -d $(INSTDIR)
	install -d $(MANDIR)
	ln -sf $(CURDIR)/cicalc $(INSTDIR)/cicalc
	ln -sf $(CURDIR)/cicalc.1 $(MANDIR)/cicalc.1

lint:
	clang-tidy *.c

clean:
	rm cicalc
