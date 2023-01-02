##
# Duck Chess
#
# @version 0.1
##

CC = gcc

all: chess src/main.c
	$(CC) -g -o duck_chess src/main.c src/chess.o src/console.o

chess: console src/chess.c src/chess.h
	$(CC) -g -o src/chess.o -c src/chess.c

console: src/console.c src/console.h
	$(CC) -g -o src/console.o -c src/console.c

clean:
	rm -f src/*.o duck_chess

# end
