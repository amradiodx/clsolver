#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "includes.h"
#include "init.h"
#include "utils.h"

extern int movenum;
extern char usedltrs[6];

char results[243][CLWSTRLEN];

void init()
{
	/* Get possible Wordle answers per character */
	char colors[LTRRESULTSLEN + 1];
	strcpy(colors, LTRRESULTS);

	memset(usedltrs, '\0', sizeof(usedltrs));
	/* Get possible Wordle answers per word */
	const int posresults = power(LTRRESULTSLEN, CLWSTRLEN); 
	// printf("Possible combinations is %d\n", posresults);

	movenum = 0;
	int count = 0;
	for(int i = 0; i < posresults; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			results[i][j] = colors[(i / power(3, j)) % 3];
		}


		// printf("%s\n", results[i]);
	}

}
