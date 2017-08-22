ifndef $(CC)
	CC=gcc
endif
CFLAGS=-O3 -Wall -std=c99 -pedantic -g
PROGRAM=tenc

PREF=src

INCLUDE=$(PREF)/include
LIBR=$(PREF)/lib

SOURCES=$(LIBR)/*.c

.PHONY: doc

doc:
	cldoc generate $(CFLAGS) -- --output doc --report

$(PROGRAM): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM) -I$(INCLUDE) -L$(LIBR)

install: $(PROGRAM)
	cp $(PROGRAM) /usr/bin/

uninstall:
	rm /usr/bin/$(PROGRAM)