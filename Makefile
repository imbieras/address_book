CC := gcc

.PHONY: all clean

all:
	$(MAKE) -C lib
	$(MAKE) -C src

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C src clean
