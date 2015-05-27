CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=utopianTree.c maximizeXor.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLES=$(SOURCES:.c=)

all: $(SOURCES) $(EXECUTABLES)

#Add new executbles here
maximizeXor : maximizeXor.o
	$(CC) $(LDFLAGS) maximizeXor.o -o $@
utopianTree : utopianTree.o
	$(CC) $(LDFLAGS) utopianTree.o -o $@
#end

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o utopianTree maximizeXor
