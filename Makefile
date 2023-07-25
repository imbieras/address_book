CC := gcc

.PHONY: all clean

all:
	$(MAKE) -C src/lib
	$(MAKE) -C src

clean:
	$(MAKE) -C src/lib clean
	$(MAKE) -C src clean
