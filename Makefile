default: help

help:
	@echo Useful targets:
	@echo "  number2:  generate an imput files: number2.txt "
	@echo "  generator: compile the generator.c"
	@echo "  solution1: compile your programs without Memoization"
	@echo "  solution2: compile your programs without Memoization"
	@echo "  run1 run2:  run your programs through the 'time' utility"
	@echo "  clean:  delete all generated files"

#########################
# workload generation

number2.txt:
	./generator > $@

#########################
## program compilation

generator: generator.c
	gcc -o generator generator.c

solution1: main6.c
	gcc  -pthread -o solution1 main6.c 

solution2: main7.c
	gcc  -pthread -O3 solution2 main7.c 

# add your own rules when you create new programs

#########################
## program execution

run1: solution1
	time ./solution1

run2: solution2
	time ./solution2

#########################
## utilities

clean:
	rm -f solution2 solution1 number2.txt

