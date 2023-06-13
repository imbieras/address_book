CC:=gcc
CFLAGS:=-Wall -Wextra -pedantic -std=c99
SOURCES:=$(wildcard *.c)
OBJS:=$(SOURCES:.c=.o)
BIN:=address_book

.PHONY: ALL clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(BIN) $(OBJS)
