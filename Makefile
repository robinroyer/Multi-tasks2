default: help

help:
	@echo Useful targets:
	@echo "  number2:  generate an imput files "
	@echo "  generator: compile the generator"
	@echo "  ResolutionAvecStockage ResolutionSansStockage: compile your programs"
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

resolutionSansStockage: main6.c
	gcc  -pthread -o resolutionSansStockage main6.c 

resolutionAvecStockage: main7.c
	gcc  -pthread -o resolutionAvecStockage main7.c 

# add your own rules when you create new programs

#########################
## program execution

run1: resolutionSansStockage
	time ./resolutionSansStockage

run2: resolutionAvecStockage
	time ./resolutionAvecStockage

#########################
## utilities

clean:
	rm -f resolutionSansStockage resolutionAvecStockage tiny.txt small.txt medium.txt large.txt many.txt 

