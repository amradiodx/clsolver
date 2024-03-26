#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes.h"
#include "lists.h"


#define WORD_COUNT 0
#define ALLOCATED 1
#define LIST_START 2


_ulonglong* word_list[GUESSES_ALLOWED];


int init_word_list()
{
	for(int i = 0; i < GUESSES_ALLOWED; ++i)
	{
		word_list[i] = (_ulonglong*) malloc(BLOCK_SIZE * sizeof(_ulonglong));
		if(word_list[i] == NULL)
		{
			printf("word_list allocation failed!\n");
			return EXIT_FAILURE;
		}
		word_list[i][WORD_COUNT] = 0ULL;
		word_list[i][ALLOCATED] = BLOCK_SIZE;
	}
	return EXIT_SUCCESS;
}


_ulonglong get_word(int idx)
{
	return word_list[0][idx + LIST_START];
}

int add_word(int guess, char w[])
{
	_ulonglong* words = word_list[guess];
	_ulonglong* pwc = &words[WORD_COUNT];
	if((words[WORD_COUNT] + LIST_START) >= words[ALLOCATED])
	{
		words[ALLOCATED] += BLOCK_SIZE;
		word_list[guess] = realloc(word_list[guess], sizeof(_ulonglong) * words[ALLOCATED]);
		printf("reallocation at element %llu\n", words[WORD_COUNT] + LIST_START);
		words = word_list[guess];
		pwc = &words[WORD_COUNT];
	}

	strncpy((char*) &words[LIST_START + (*pwc)++], w, sizeof(_ulonglong));

	return words[WORD_COUNT];
}

_ulonglong get_word_count(int idx)
{
	return word_list[idx][WORD_COUNT];
}

size_t get_allocated(int idx)
{
	return word_list[idx][ALLOCATED];
}
