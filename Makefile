CC=gcc
FLAGS=-std=c99 -Wall -g
INCLUDES=-Iheaders

test: tests/test_interpret.c src/cpu.c headers/cpu.h
	$(CC) $(FLAGS) $(INCLUDES) tests/test_interpret.c src/cpu.c -o build/test_interpret
	valgrind --leak-check=full build/test_interpret

clean:
	rm -f build/*