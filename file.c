#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "includes.h"
#include "file.h"


FILE* rfptr;
// FILE* wfptr;
FILE* logptr;

extern int mov_num;




/* Open the current list of words */
int
openwords()
{
	char wordfile[32];
	sprintf(wordfile, WORDFILE, mov_num);
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
int
open_log()
{	
	printf("Opening %s for writing\n", LOGFILE);
	logptr = fopen(LOGFILE, "w");
	if(logptr == NULL)
	{

		printf("%s file open error!\n", LOGFILE);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int
log_entry(char log[])
{
	if(logptr == NULL)
	{
		printf("log_entry failed\n");
		return EXIT_FAILURE;
	}

	return fputs(log, logptr);
}

int
close_log()
{
	return fclose(logptr);
}

/* Open the list of words for the next guess */
/* int openwwords()
{	
	char wordfile[32];
	sprintf(wordfile, WORDFILE, mov_num + 1);
	
	printf("Opening %s for writing\n", wordfile);
	wfptr = fopen(wordfile, "w");
	if(wfptr == NULL)
	{

		printf("%s file open error!\n", wordfile);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
} */

void
clrewind()
{
	rewind(rfptr);
}

char*
getword(char* word, size_t size)
{
	if(rfptr == NULL)
	{
		return NULL;
	}
	
	return fgets(word, size + 1, rfptr);
}


int
closewords()
{
	return fclose(rfptr);
}

