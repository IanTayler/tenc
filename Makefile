ifndef $(CC)
	CC=gcc
endif
CFLAGS=-O3 -Wall -std=c99 -pedantic -g -fopenmp
PROGRAM=tenc

PREF=src

INCLUDE=$(PREF)/include
LIBR=$(PREF)/lib

SOURCES=$(PREF)/*.c
INCLUDES=$(INCLUDE)/*.h

.PHONY: doc servedoc install uninstall all

all: $(PROGRAM) doc
	@echo "Finished making $(PROGRAM)"
doc:
	doxygen

servedoc: doc
	cd doc/html; python3 -m http.server 8000

$(PROGRAM): $(SOURCES) $(INCLUDES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM) -I$(INCLUDE) -L$(LIBR)

install: $(PROGRAM)
	cp $(PROGRAM) /usr/bin/

uninstall:
	rm /usr/bin/$(PROGRAM)
