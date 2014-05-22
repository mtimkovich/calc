CC=gcc
EXE=calc
LDLIBS=-ledit
CFLAGS=-Wall -g -O0

OBJECTS=calc.o token.o
HEADERS=token.h

SRC_DIR=src
OUT_OBJ=$(addprefix $(SRC_DIR)/,$(OBJECTS))
OUT_HEADERS=$(addprefix $(SRC_DIR)/,$(HEADERS))

all: $(EXE)

$(EXE): $(OUT_OBJ) 
	$(CC) $(OUT_OBJ) $(CFLAGS) $(LDLIBS) -o $(EXE)

.PHONY: clean
clean:
	rm $(OUT_OBJ) $(EXE)
