CC=gcc
CFLAGS=-pedantic -Wall -Werror -Wextra -c

all: main.o vector.o stack.o
	$(CC) $^
	
main.o: ./src/main.c ./include/stack.h ./include/vector.h
	$(CC) $(CFLAGS) $<
	
vector.o: ./src/vector.c ./include/stack.h ./include/vector.h
	$(CC) $(CFLAGS) $<

stack.o: ./src/stack.c ./include/stack.h
	$(CC) $(CFLAGS) $<
	
clean:
	rm -f main.o vector.o stack.o
