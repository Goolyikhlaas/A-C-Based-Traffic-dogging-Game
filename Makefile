# Set the compiler
CC = gcc

# Set the compiler flags
CFLAGS = -Wall -ansi -pedantic

# Default target
all: traffic

# Target for 'traffic' executable
traffic: main.o game.o terminal.o
	# Link object files to produce 'traffic'
	$(CC) $(CFLAGS) main.o game.o terminal.o -o traffic

# Compile main.c into main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Compile game.c into game.o
game.o: game.c
	$(CC) $(CFLAGS) -c game.c

# Compile terminal.c into terminal.o
terminal.o: terminal.c
	$(CC) $(CFLAGS) -c terminal.c

# Clean the build
clean:
	# Remove all object files and the executable
	rm -f *.o traffic









