main : main.o
	gcc -o -pthread main main.c
main.o:main.c
	gcc -o main.o main.c
clean:
	rm -rf *.o
