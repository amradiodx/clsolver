#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "includes.h"



int verifyword(char *word)
{
	int len = strlen(word);
	printf("String length in verifyword is %d\n", len);

	if(len != (CLWSTRLEN))
	{
		printf("Length is %d    Comparison is %d\n", len, (CLWSTRLEN - 1));
		return 0;
	}
	printf("Length okay in verifyword\n");

	for(int i = 0; i < len; ++i)
	{
		if(isalpha(word[i]) == 0)
			return 0;
	}
	return 1;
}

int verifyresults(char *word)
{
	int ret = 0;
	int len = strlen(word);

	int rslts = strspn(word, LTRRESULTS);

	if(len == rslts)
	{
		ret = 1;
	}
	
	return ret;
}
