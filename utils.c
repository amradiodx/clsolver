#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "includes.h"




bool remnewln(char s [])
{	
	bool ret = false;
	char* r = strrchr(s, '\n');

	if(r != NULL)
	{
		*r = '\0';
		ret = true;
	}

	return ret;
}

int power(int x, int n)
{
	int i, p;

	if(n == 0)
	{
		return 1;
	}

	for(p = 1; n > 0; --n)
	{
		p = p * x;
	}

	return (p);
}

void clrcntarray(struct cntarray* ca)
{
	ca->idx = -1;
	memset(ca->ar, '\0', sizeof(ca->ar));
}

bool addcntarray(struct cntarray* ca, short sh, char c)
{
	bool ret = true;
	if(++ca->idx < sizeof(ca->ar))
	{
		ca->ar[ca->idx] = c;
	}
	else
	{
		ret = false;
	}
	return ret;
}

int getcharcnt(char s[], char c)
{
	int count = 0;
	char* found = NULL;
	while ((found = strchr(s, c)) != NULL)
	{
		count++;
		found = '\0';
	}
	return count;
}

