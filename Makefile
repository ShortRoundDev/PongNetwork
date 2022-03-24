CC=clang
INC=inc
LIBS=-lSDL2  -lSDL2_ttf -lm
CFLAGS=-I$(INC) $(LIBS) -g -O0
SRC=src
OBJ=obj
SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
BIN=bin

all: $(OBJS) | $(BIN)
	$(CC) $^ -o $(BIN)/shooter $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm $(BIN)/* $(OBJ)/*