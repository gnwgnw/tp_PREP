all: dz2

dz2: main.o matrix.o
	gcc main.o matrix.o -o dz2.out -lm 

main.o: main.c
	gcc -std=c99 -c -g main.c -lm 

matrix.o: matrix.c
	gcc -std=c99 -c -g matrix.c -lm 

clean:
	rm -rf *.o dz_1

