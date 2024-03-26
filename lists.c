#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "includes.h"
#include "lists.h"


#define WORD_COUNT 0
#define STARTING_WC 0
#define ALLOCATED 1
#define LIST_START 2


uint64_t* word_list[GUESSES_ALLOWED];


int init_word_list()
{
	for(int i = 0; i < GUESSES_ALLOWED; ++i)
	{
		word_list[i] = (uint64_t*) malloc(BLOCK_SIZE * sizeof(uint64_t));
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


uint64_t get_word(int guess, int idx)
{
	return word_list[guess][idx + LIST_START];
}

int add_word(int guess, char w[])
{
	uint64_t* words = word_list[guess];
	uint64_t* pwc = &words[WORD_COUNT];
	if((words[WORD_COUNT] + LIST_START) >= words[ALLOCATED])
	{
		words[ALLOCATED] += BLOCK_SIZE;
		word_list[guess] = realloc(word_list[guess], sizeof(uint64_t) * words[ALLOCATED]);
		// printf("reallocation at element %llu\n", words[WORD_COUNT] + LIST_START);
		words = word_list[guess];
		pwc = &words[WORD_COUNT];
	}

	strncpy((char*) &words[LIST_START + (*pwc)++], w, sizeof(uint64_t));

	return words[WORD_COUNT];
}

uint64_t get_starting_wc()
{
	return get_word_count(STARTING_WC);
}

uint64_t get_word_count(int idx)
{
	return word_list[idx][WORD_COUNT];
}

/* get_total_size() returns total element count, which will
   be higher than word count */
uint64_t get_total_size(int idx)
{
	return word_list[idx][WORD_COUNT] + LIST_START;
}

/* get_allocated() returns the number of allocated elements,
   not allocated bytes */
size_t get_allocated(int idx)
{
	return word_list[idx][ALLOCATED];
}
