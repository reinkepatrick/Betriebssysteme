CFLAGS = -std=c11 -g -I$(INCLUDE)
INCLUDE = ../include

file: src/main.o
	gcc -o $@ $^

.PHONY: clean
clean:
	rm -rf src/*.o file *.~ data/new.txt
