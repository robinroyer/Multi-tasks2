main6 : main6.o
	gcc -o  main6 main6.c -pthread
main6.o:main6.c
	gcc -o main6.o main6.c -pthread
clean:
	rm -rf *.o
