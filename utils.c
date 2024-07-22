#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include "includes.h"
#include "utils.h"


void
make_lower(char s[])
{
	for(size_t i = 0; i < strlen(s); ++i)
	{
		s[i] = tolower(s[i]);
	}
}


int
power(int x, int n)
{
	int p;

	if(n == 0)
		return 1;

	for(p = 1; n > 0; --n)
		p = p * x;

	return (p);
}


void
strclr(char str[], size_t size)
{
	memset(str, '\0', size);
}


int
add_char_to_string(char str[], char c, size_t size)
{
	size_t len = strlen(str);
	if(len >= (size - 1))
	{
		return EXIT_FAILURE;
	}

	if(strchr(str, c) == NULL)
	{
		str[len] = c;
	}

	return EXIT_SUCCESS;
}



void
str_intrsct(const char str1[], const char str2[], char rslt[], size_t rslt_size)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	strclr(rslt, rslt_size);

	for(int i = 0; i < len1; ++i)
	{
		for(int j = 0; j < len2; ++j)
		{
			if(str1[i] == str2[j])
			{
				add_char_to_string(rslt, str1[i], rslt_size);
			}
		}
	}
}


void
init_dupes(struct duplicates *dupes)
{
	dupes->count = 0;
	dupes->locations[0] = -1;
}

bool
has_mult_ltrs(char s[])
{
	char buf[8];
	strncpy(buf, s, sizeof(buf));
	
	for (size_t i = 0; i < strlen(s); ++i) {
		if (strchrcnt(buf, s[i], sizeof(buf)) > 1) {
			return true;
		}
	}

	return false;
}

int
strchrcnt(char str[], char c, size_t size)
{
	int count = 0;
	char buf[size];
	strncpy(buf, str, size);
	char* found = NULL;

	while ((found = strchr(buf, c)) != NULL) {
		count++;
		*found = '-';
	}
	return count;
}


/*
float
get_entropy(unsigned int word_count, unsigned int total_words)
{
	float probability = ((float) word_count) / 
		((float) total_words);
			
	return probability * log2f(1.0 / probability);
} */

float
get_entropy(unsigned int word_count, unsigned int total_words)
{
	float probability = ((float) word_count) / 
		((float) total_words);
			
	return -(probability * log2f(probability));
}
