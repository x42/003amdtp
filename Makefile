CFLAGS?=-Wall -O3
CFLAGS+=-DTEST_MAIN

digimagic: digimagic.c

clean:
	rm digimagic

check: digimagic
	./digimagic

.PHONY: clean check
