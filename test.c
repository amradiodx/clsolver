#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test.h"

int main()
{
	char teststring[] = "this is a test";
	char testchar = 'z';
	int count = getcharcnt(teststring, testchar);
	
	printf("String %s has %d %c\n", teststring, count, testchar);
	


	return 0;
}



int getcharcnt(char s[], char c)
{
	int count = 0;
	char* found = NULL;
	while ((found = strchr(s, c)) != NULL)
	{
		count++;
		*found = '-';
	}
	return count;
}

