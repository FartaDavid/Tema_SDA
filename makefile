$CFLAGS = -g -Wall -Wextra
$CC = gcc

build:
	$(CC) -o tema1 main.c $(CFLAGS)

run: build
	./tema1

clean: 
	rm -f tema1
