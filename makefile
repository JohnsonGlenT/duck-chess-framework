##
# Duck Chess
#
# @version 0.1
##

CC = gcc

all: chess src/main.c
	$(CC) -o duck_chess src/main.c src/chess.o

chess: src/chess.c src/chess.h
	$(CC) -o src/chess.o -c src/chess.c

clean:
	rm -f src/*.o duck_chess

# end
