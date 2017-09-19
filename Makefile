ifndef $(CC)
	CC=gcc
endif
CFLAGS=-O3 -Wall -pedantic -g -fopenmp -std=gnu99 -march=native
LIBCFLAGS=$(CFLAGS) -shared -fPIC
PROGRAM=tenc
LIBRARY=libtenc.so

PREF=src

INCLUDE=$(PREF)/include
UTILSINCLUDE=$(PREF)/utils/include
LIBR=$(PREF)/lib

LIBSOURCES=$(LIBR)/*.c
UTILSSOURCES=$(PREF)/utils/*.c
SOURCES=$(PREF)/*.c $(LIBSOURCES) $(UTILSSOURCES)
INCLUDES=$(INCLUDE)/*.h

.PHONY: doc servedoc install uninstall all test

all: $(PROGRAM) $(LIBRARY)
doc:
	doxygen

servedoc: doc
	cd doc/html; python3 -m http.server 8000

$(PROGRAM): $(SOURCES) $(INCLUDES) Makefile
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM) -I$(INCLUDE) -I$(UTILSINCLUDE)
	@echo "Finished making $(PROGRAM)"

$(LIBRARY): $(SOURCES) $(INCLUDES) Makefile
	$(CC) $(LIBCFLAGS) $(SOURCES) -o $(LIBRARY) -I$(INCLUDE) -I$(UTILSINCLUDE)
	@echo "Finished making $(LIBRARY)"

install: $(PROGRAM)
	cp $(PROGRAM) /usr/local/bin/
	cp $(LIBRARY) /usr/local/lib/

uninstall:
	rm /usr/bin/$(PROGRAM)

TESTSOURCES=test/*.c
TESTINCLUDE=test/include/
TESTINCLUDES=test/include/*.h
tests: $(TESTSOURCES) $(LIBSOURCES) $(INCLUDES) $(TESTINCLUDES) Makefile
	$(CC) $(CFLAGS) $(LIBSOURCES) $(UTILSSOURCES) $(TESTSOURCES) -o tests -I$(TESTINCLUDE) \
	-I$(INCLUDE) -I$(UTILSINCLUDE)
	./tests

test: tests
