CC = gcc
CFLAGS = -Wall -Wextra -I include
SRC = src/main.c src/Board.c src/Tile.c src/Menu.c src/Display.c src/Timer.c src/File.c
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
BIN = bin/minesweeper

$(BIN): $(OBJ) | bin
	$(CC) -o $@ $^

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

bin:
	mkdir -p bin

data:
	mkdir -p data

run: $(BIN) | data
	./$(BIN)

clean:
	rm -rf obj bin

.PHONY: run clean