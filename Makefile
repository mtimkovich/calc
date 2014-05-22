CC=gcc
EXE=calc
LDLIBS=-ledit
CFLAGS=-Wall -g -O0
SRC_DIR=src
OBJECTS=calc.o token.o
OUT_OBJ=$(addprefix $(SRC_DIR)/,$(OBJECTS))
HEADERS=token.h
OUT_HEADERS=$(addprefix $(SRC_DIR)/,$(HEADERS))

all: $(EXE)

$(EXE): $(OUT_OBJ) 
	$(CC) $(OUT_OBJ) $(CFLAGS) $(LDLIBS) -o $(EXE)

.PHONY: clean
clean:
	rm $(OBJECTS) $(EXE)
