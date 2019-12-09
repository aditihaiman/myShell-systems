all: shell.o 
	gcc -o a.out shell.o

shell.o: shell.c
	gcc -c shell.c

run:
	./a.out