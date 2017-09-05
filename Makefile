ifndef $(CC)
	CC=gcc
endif
CFLAGS=-O3 -Wall -pedantic -g -fopenmp
PROGRAM=tenc

PREF=src

INCLUDE=$(PREF)/include
LIBR=$(PREF)/lib

LIBSOURCES=$(LIBR)/*.c
SOURCES=$(PREF)/*.c $(LIBSOURCES)
INCLUDES=$(INCLUDE)/*.h

.PHONY: doc servedoc install uninstall all test

all: $(PROGRAM)
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

TESTSOURCES=test/*.c
TESTINCLUDE=test/include/
TESTINCLUDES=test/include/*.h
tests: $(TESTSOURCES) $(LIBSOURCES) $(INCLUDES) $(TESTINCLUDES)
	$(CC) $(CFLAGS) $(LIBSOURCES) $(TESTSOURCES) -o tests -I$(TESTINCLUDE) \
	-I$(INCLUDE)
	./tests

test: tests
