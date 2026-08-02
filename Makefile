CC ?= cc
CFLAGS :=
ASSETDIR ?= $(CURDIR)
INSTDIR ?= /usr/local/bin

build: main.c format
	$(CC) *.c -o cicalc -pedantic -Wall -Werror -Wextra -O3 -march=native -lm -std=c99

format:
	clang-format -i *.c

install: cicalc
	install -d $(INSTDIR)
	ln -sf $(CURDIR)/cicalc $(INSTDIR)/cicalc

lint:
	clang-tidy *.c

clean:
	rm cicalc
