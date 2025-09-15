CFLAGS := -Wall -Wextra -pedantic -std=c11
CFLAGS += -g -O0

run: build/main
	@./build/main

build:
	mkdir -p build

build/main: src/main.c | build
	$(CC) -E $< -o $@.i
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -fr build/
