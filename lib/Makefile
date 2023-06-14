GFLAGS := -Wall -Wextra -pedantic -std=c99 -O2
CFLAGS := $(GFLAGS) -fPIC
SOURCES := $(wildcard *.c)
OBJS := $(SOURCES:.c=.o)
LIB := liblinkedlist.so

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) -shared -o $@ $^

clean:
	$(RM) $(LIB) $(OBJS)
