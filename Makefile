CFLAGS=-Wall -Wextra


clwordle: clwordle.o init.o words.o file.o verify.o utils.o lists.o
	@echo "Linking clwordle"
	cc -lm clwordle.o  init.o words.o file.o verify.o utils.o lists.o -o clwordle


clwordle.o: clwordle.c
	@echo "Compiling clwordle.c"
	cc $(CFLAGS) -c clwordle.c

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

clean:
	@echo "Removing object files"
	@rm clwordle.o init.o words.o file.o verify.o utils.o lists.o 

debug:
	@echo "Compiling debug version"
	cc -g -lm clwordle.c init.c words.c file.c verify.c utils.c lists.c -o clwordle
