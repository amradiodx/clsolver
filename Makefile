


clwordle: clwordle.o init.o words.o file.o verify.o utils.o
	@echo "Linking clwordle"
	@gcc clwordle.o  init.o words.o file.o verify.o utils.o -o clwordle


clwordle.o: clwordle.c
	@echo "Compiling clwordle.c"
	@gcc -c clwordle.c

init.o: init.c
	@echo "Compiling init.c"
	@gcc -c init.c

words.o: words.c
	@echo "Compiling words.c"
	@gcc -c words.c


file.o: file.c
	@echo "Compiling file.c"
	@gcc -c file.c

verify.o: verify.c
	@echo "Compiling verify.c"
	@gcc -c verify.c

utils.o: utils.c
	@echo "Compiling utils.c"
	@gcc -c utils.c

clean:
	@echo "Removing object files"
	@rm clwordle.o init.o words.o file.o verify.o utils.o 
