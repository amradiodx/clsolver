#include <stdio.h>
#include <stdlib.h>
#include "includes.h"
#include "file.h"


FILE* rfptr;
FILE* wfptr;

extern int movenum;


/* Open the current list of words */
int openwords()
{
	char wordfile[32];
	sprintf(wordfile, WORDFILE, movenum);
	printf("Opening %s for reading\n", wordfile);
	rfptr = fopen(wordfile, "r");
	if(rfptr == NULL)
	{
		printf("%s file open error!\n", wordfile);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/* Open the list of words for the next guess */
int openwwords()
{	
	char wordfile[32];
	sprintf(wordfile, WORDFILE, movenum + 1);
	
	printf("Opening %s for writing\n", wordfile);
	wfptr = fopen(wordfile, "w");
	if(wfptr == NULL)
	{

		printf("%s file open error!\n", wordfile);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/*
int rdwrdlst()
{
	char s[7];

	while (fgets(s, sizeof(s), fptr[movenum]) != NULL)
	{
		printf("%s", s);
	}

	printf("\n");

	fclose(fptr[movenum]);

	return 0;
} */

char* getword(char* word)
{
	if(rfptr == NULL)
	{
		return NULL;
	}
	
	return fgets(word, sizeof(word), rfptr);
}

int putword(char* word)
{
	char nlword[32];
	sprintf(nlword, "%s\n", word);
	if(wfptr == NULL)
	{
		printf("putword failed\n");
		return EXIT_FAILURE;
	}

	return fputs(nlword, wfptr);
}

int closewords()
{
	return fclose(rfptr);
}

int closewwords()
{
	return fclose(wfptr);
}
