main : main.o
	gcc -o  main main.c -pthread
main.o:main.c
	gcc -o main.o main.c -pthread
clean:
	rm -rf *.o
