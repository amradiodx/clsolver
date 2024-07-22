#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "includes.h"



int
verifyword(char *word)
{
	int len = strlen(word);

	if(len != (WORDLEN))
	{
		printf("Length is %d    Comparison is %d\n", len, (WORDLEN - 1));
		return 0;
	}

	for(int i = 0; i < len; ++i)
	{
		if(isalpha(word[i]) == 0)
			return 0;
	}
	return 1;
}

int
verifyresults(char *word)
{
	int ret = 0;
	int len = strlen(word);
	if(len != WORDLEN) {
		return 0;
	}

	int rslts = strspn(word, TILE_COLORS);

	if(len == rslts)
	{
		ret = 1;
	}
	
	return ret;
}
