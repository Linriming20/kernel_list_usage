all: main

main: main.c list.h
	gcc $^ -o $@

clean:
	rm -f main
