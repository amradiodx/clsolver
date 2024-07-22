CFLAGS=-Wall -Wextra -g -std=c99
CC=gcc

clsolver: clsolver.o init.o words.o file.o verify.o utils.o lists.o letters.o database.o
	@echo "Linking clsolver"
	$(CC) -lm -lsqlite3 clsolver.o  init.o words.o file.o verify.o utils.o lists.o letters.o  database.o -o clsolver


clsolver.o: clsolver.c
	@echo "Compiling clsolver.c"
	$(CC) $(CFLAGS) -c clsolver.c

init.o: init.c
	@echo "Compiling init.c"
	$(CC) $(CFLAGS) -c init.c

words.o: words.c
	@echo "Compiling words.c"
	$(CC) $(CFLAGS) -c words.c


file.o: file.c
	@echo "Compiling file.c"
	$(CC) $(CFLAGS) -c file.c

verify.o: verify.c
	@echo "Compiling verify.c"
	$(CC) $(CFLAGS) -c verify.c

utils.o: utils.c
	@echo "Compiling utils.c"
	$(CC) $(CFLAGS) -c utils.c

lists.o: lists.c
	@echo "Compiling lists.c"
	$(CC) $(CFLAGS) -c lists.c

letters.o: letters.c
	@echo "Compiling letters.c"
	$(CC) $(CFLAGS) -c letters.c

database.o: database.c
	@echo "Compiling database.c"
	$(CC) $(CFLAGS) -c database.c

clean:
	@echo "Removing object files"
	@rm clsolver.o init.o words.o file.o verify.o utils.o lists.o letters.o database.o

debug:
	@echo "Compiling debug version"
	cc -g -lm  clsolver.c init.c words.c file.c verify.c utils.c lists.c letters.c database.c -o clsolver
