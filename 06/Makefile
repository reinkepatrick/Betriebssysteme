CFLAGS = -pthread -std=c11 -Wall -g -I$(INCLUDE)
INCLUDE = ../include

threads: src/main.o src/miniz.o
	gcc -o $@ $^

.PHONY: clean
clean:
	rm -rf src/*.o threads *.~
