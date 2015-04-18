main7 : main7.o
	gcc -o  main7 main7.c -pthread
main7.o:main7.c
	gcc -o main7.o main7.c -pthread
clean:
	rm -rf *.o
