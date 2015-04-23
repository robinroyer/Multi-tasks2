default: help

help:
	@echo Useful targets:
	@echo "  small.txt medium.txt large.txt many.txt:  generate some input files "
	@echo "  ResolutionAvecStockage ResolutionSansStockage: compile your programs"
	@echo "  run1 run2:  run your programs through the 'time' utility"
	@echo "  clean:  delete all generated files"

#########################
# workload generation

tiny.txt:
	./generator.cs 20 20 0 > $@

small.txt:
	./generator.cs 20 32 50 > $@

medium.txt:
	./generator.cs 20 50 50 > $@

large.txt:
	./generator.cs 20 64 50 > $@

many.txt:
	./generator.cs 1000 50 75 > $@

#########################
## program compilation

resolutionSansStockage: main6.c
	gcc  -pthread -o resolutionSansStockage main6.c 

ResolutionAvecStockage: main7.c
	gcc  -pthread -o resolutionSansStockage main7.c 

# add your own rules when you create new programs

#########################
## program execution

run1: resolutionSansStockage
	time ./resolutionSansStockage

run2: ResolutionAvecStockage
	time ./ResolutionAvecStockage

#########################
## utilities

clean:
	rm -f resolutionSansStockage ResolutionAvecStockage tiny.txt small.txt medium.txt large.txt many.txt 

