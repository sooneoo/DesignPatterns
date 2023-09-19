CC=gcc

CFLAGS=-Wall -Wextra -pedantic
LIBS=
OUTPUT=strategy

all: main.c
	$(CC) $(CFLAGS) main.c $(LIBS) -o $(OUTPUT)


exec: all
	./$(OUTPUT)
