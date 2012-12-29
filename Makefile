CFLAGS?=-Wall -O3
CFLAGS+=-DTEST_MAIN

digimagic: digiselftest.c digimagic.c digimagic.h

clean:
	rm digimagic

check: digimagic
	./digimagic

.PHONY: clean check
