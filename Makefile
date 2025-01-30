CC=gcc
FLAGS=-std=c99 -g
INCLUDES=-Iheaders

test: tests/nestest.c src/cpu.c src/bus.c src/rom.c
	$(CC) $(FLAGS) $(INCLUDES) tests/nestest.c src/cpu.c src/bus.c src/rom.c -o build/nestest
	./build/nestest

clean:
	rm -f build/*