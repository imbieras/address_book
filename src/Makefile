GFLAGS := -Wall -Wextra -pedantic -std=c99 -O2
CFLAGS := $(GFLAGS)
SOURCES := $(wildcard *.c)
OBJS := $(SOURCES:.c=.o)
BIN := ../address_book
LDFLAGS := -L../lib -Wl,-rpath='./lib' -llinkedlist 
INCLUDE := -I../lib

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(BIN) $(OBJS)
