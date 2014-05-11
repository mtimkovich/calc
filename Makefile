CC=gcc
EXE=calc
LDLIBS=-ledit
CFLAGS=-Wall
OBJECTS=calc.o token.o

all: $(EXE)

$(EXE): $(OBJECTS) token.h
	$(CC) $(OBJECTS) $(CFLAGS) $(LDLIBS) -o $(EXE)

.PHONY: clean
clean:
	rm $(OBJECTS) $(EXE)
