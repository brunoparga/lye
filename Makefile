CC = gcc
CFLAGS = -g -Wextra -Wall -Wpedantic -Wshadow -Wformat=2 -Wconversion -Wnull-dereference -Wsign-conversion -ggdb3 -std=c99 -fsanitize=address
LDFLAGS = -ledit -lm
COMPILE = $(CC) -c $(CFLAGS) $< -o $@

SOURCES = src/main.c src/calc.c src/env.c src/eval.c src/function.c src/list.c src/parser.c src/repl.c src/value.c lib/mpc.o utils/file.c
OBJECTS = src/main.c build/calc.o build/env.o build/eval.o build/function.o build/list.o build/parser.o build/repl.o build/value.o build/file.o src/assert.h utils/realloc_string.h

test: test/test.c build/lye
	$(CC) $(CFLAGS) test/test.c -o lye-test
	./lye-test

build/lye: $(OBJECTS)
	$(CC) $(CFLAGS) -o lye $(SOURCES) $(LDFLAGS)

build/repl.o: src/repl.c src/repl.h build/parser.o
	$(COMPILE)

build/parser.o: src/parser.c src/parser.h build/eval.o build/value.o lib/mpc.o
	$(COMPILE)

build/eval.o: src/eval.c src/eval.h build/env.o build/calc.o build/list.o build/value.o
	$(COMPILE)

build/function.o: src/function.c src/function.h build/value.o
	$(COMPILE)

build/calc.o: src/calc.c src/calc.h build/value.o
	$(COMPILE)

build/list.o: src/list.c src/list.h build/value.o
	$(COMPILE)

build/env.o: src/env.c src/env.h build/calc.o build/list.o build/value.o
	$(COMPILE)

build/value.o: src/value.c src/value.h
	$(COMPILE)

build/file.o: utils/file.c utils/file.h
	$(COMPILE)

# I might want to delete this is it interferes with gdb
.PHONY: clean

clean:
	@rm -f lye lye-test build/*.o