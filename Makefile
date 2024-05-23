CFLAGS=-Wall -Wextra -g


clsolver: clsolver.o init.o words.o file.o verify.o utils.o lists.o letters.o hash.o
	@echo "Linking clsolver"
	cc -lm clsolver.o  init.o words.o file.o verify.o utils.o lists.o letters.o hash.o -o clsolver


clsolver.o: clsolver.c
	@echo "Compiling clsolver.c"
	cc $(CFLAGS) -c clsolver.c

init.o: init.c
	@echo "Compiling init.c"
	cc $(CFLAGS) -c init.c

words.o: words.c
	@echo "Compiling words.c"
	cc $(CFLAGS) -c words.c


file.o: file.c
	@echo "Compiling file.c"
	cc $(CFLAGS) -c file.c

verify.o: verify.c
	@echo "Compiling verify.c"
	cc $(CFLAGS) -c verify.c

utils.o: utils.c
	@echo "Compiling utils.c"
	cc $(CFLAGS) -c utils.c

lists.o: lists.c
	@echo "Compiling lists.c"
	cc $(CFLAGS) -c lists.c

letters.o: letters.c
	@echo "Compiling letters.c"
	cc $(CFLAGS) -c letters.c

hash.o: hash.c
	@echo "Compiling hash.c"
	cc $(CFLAGS) -c hash.c

clean:
	@echo "Removing object files"
	@rm clsolver.o init.o words.o file.o verify.o utils.o lists.o letters.o hash.o

debug:
	@echo "Compiling debug version"
	cc -g -lm  clsolver.c init.c words.c file.c verify.c utils.c lists.c letters.c hash.c -o clsolver
