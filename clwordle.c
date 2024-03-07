#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "includes.h"
#include "init.h"
#include "verify.h"
#include "file.h"
#include "words.h"
#include "utils.h"

int movenum;

int main(int argc, char **argv)
{
	char guess[7];
	char resultsword[7];

	
	init();

	do
	{
		/* Get starting word */
		getguess(guess);

		/* Get the results */
		getresults(resultsword);

		/* Get unused letters */
		char unusedltrs[CLWSTRLEN + 1];
		char usedltrs[CLWSTRLEN + 1];

		getunusedltrs(guess, resultsword, unusedltrs, usedltrs);

		printf("Unused: %s, used: %s\n", unusedltrs, usedltrs);

		if(openwords() != EXIT_SUCCESS)
		{
			printf("Word open error\n");
			return EXIT_FAILURE;
		}

		if(openwwords() != EXIT_SUCCESS)
		{
			printf("Word open error\n");
			return EXIT_FAILURE;
		}


		char s[CLWSTRLEN + 2];
		while(getword(s) != NULL)
		{
			/* Remove newline character */
			remnewln(s);

			if(ispossibleword(guess, s, resultsword, unusedltrs) == true)
			{
				printf("%s is possible\n", s);
				if(putword(s) == EOF)
				{
					printf("EXIT_FAILURE from putwords\n");
					return EXIT_FAILURE;
				}
			}
		}

		if(closewords() != EXIT_SUCCESS)
		{
			printf("Word close error\n");
			return EXIT_FAILURE;
		}

		if(closewwords() != EXIT_SUCCESS)
		{
			printf("Word close error\n");
			return EXIT_FAILURE;
		}

		printf("Word list closed\n");

		// rdwrdlst();
		printf("You entered %s\n", guess);

	} while(++movenum <= 6 && (issolved(resultsword) != true));

	char fnt[] = "wordlist%d.txt";
	char fn[20];
	sprintf(fn, fnt, movenum);
	printf("%s\n", fn);

	return 0;

}



int wordfinder(char wlword[], char result[])
{
	bool greenletter = false;
	char workword[CLWSTRLEN + 1];
	strncpy(wlword, workword, CLWSTRLEN + 1);

	int i;
	for(i = 0; i < CLWSTRLEN; ++i)
	{
		if(isupper(result[i]) && wlword[i] == result[i])
		{
			wlword[i] = result[i] = '-';
		}
	}
	for(i = 0; i < CLWSTRLEN; ++i)
	{
		for(int j = 0; j < CLWSTRLEN; ++j)
		{
			if(wlword[j] == result[i])
			{
				wlword[j] = result[i] = '-';
			}
		}
	}
	return 0;
}

