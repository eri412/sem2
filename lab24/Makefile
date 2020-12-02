CC = gcc
CFLAGS = -pedantic -Wall -Wextra -Wno-missing-field-initializers -I./include

INCLUDE_PATH = ./include
BIN_PATH = ./bin
SRC_PATH = ./src

.PHONY: all clean

all: $(BIN_PATH)/main.o $(BIN_PATH)/token.o $(BIN_PATH)/token_vec.o $(BIN_PATH)/parse.o $(BIN_PATH)/token_tree.o
	$(CC) $(CFLAGS) $^ -o prog -lm

$(BIN_PATH)/main.o: $(SRC_PATH)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_PATH)/token.o: $(SRC_PATH)/token.c $(INCLUDE_PATH)/token.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_PATH)/token_vec.o: $(SRC_PATH)/token_vec.c $(INCLUDE_PATH)/token_vec.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_PATH)/parse.o: $(SRC_PATH)/parse.c $(INCLUDE_PATH)/parse.h $(INCLUDE_PATH)/token_vec.h $(INCLUDE_PATH)/token_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_PATH)/token_tree.o: $(SRC_PATH)/token_tree.c $(INCLUDE_PATH)/token_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_PATH)/* ./main
