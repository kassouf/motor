PMKGCC = PMK_GCC	#use the GCC optimizations.  Comment this line out if you don't want GCC optimizations
COMP_OPTS = -Wall



bin/motor: bin/util.o src/motor.c
	gcc -D$(PMKGCC) -o bin/motor -I./src -lm ./bin/util.o ./src/motor.c $(COMP_OPTS)

bin/util.o: src/util.h src/util.c
	gcc -c -D$(PMKGCC) -o bin/util.o -I./src -lm ./src/util.c $(COMP_OPTS)

clean:
	rm bin/*