CFLAGS = -pthread -std=c11 -Wall -g -I$(INCLUDE)
INCLUDE = ../include

scheduling: src/main.o src/global.o src/lists.o
	gcc -o $@ $^

.PHONY: clean
clean:
	rm -rf src/*.o scheduling *.~
