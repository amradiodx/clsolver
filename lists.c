#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "includes.h"
#include "lists.h"


#define WORD_COUNT 0
#define STARTING_WC 0
#define ALLOCATED 1
#define LIST_START 2


uint64_t* word_list[GUESSES_ALLOWED];

struct wordlist wrdlst[GUESSES_ALLOWED];

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

		wrdlst[i].words = (uint64_t*) malloc(BLOCK_SIZE * sizeof(uint64_t));
		wrdlst[i].count = 0;
		wrdlst[i].alloc_elmnts = BLOCK_SIZE;
		wrdlst[i].dup_ltrs = false;
	}
	return EXIT_SUCCESS;
}

char 
*get_word(int guess, int idx)
{
	return (char*) &word_list[guess][idx + LIST_START];
}


char 
*get_word2(int guess, int idx)
{
	return (char*) &wrdlst[guess].words[idx];
}

int add_word(int guess, char w[])
{
	uint64_t* words = word_list[guess];
	uint64_t* pwc = &words[WORD_COUNT];
	if((words[WORD_COUNT] + LIST_START) >= words[ALLOCATED])
	{
		words[ALLOCATED] += BLOCK_SIZE;
		word_list[guess] = realloc(word_list[guess], sizeof(uint64_t) * words[ALLOCATED]);
		words = word_list[guess];
		pwc = &words[WORD_COUNT];
	}

	strncpy((char*) &words[LIST_START + (*pwc)++], w, sizeof(uint64_t));

	return words[WORD_COUNT];
}

int
add_word2(int guess, char w[], bool dups)
{
	uint64_t* words = wrdlst[guess].words;
	if (wrdlst[guess].count >= wrdlst[guess].alloc_elmnts) {
		wrdlst[guess].alloc_elmnts += BLOCK_SIZE;
		wrdlst[guess].words = realloc(wrdlst[guess].words,
				sizeof(uint64_t) * wrdlst[guess].alloc_elmnts);
		words = wrdlst[guess].words;
	}

	strncpy((char*) &words[wrdlst[guess].count++], w, sizeof(uint64_t));
	wrdlst[guess].dup_ltrs = dups;

	return wrdlst[guess].count;
}

uint64_t get_starting_wc()
{
	return get_word_count(STARTING_WC);
}

int get_starting_wc2()
{
	return get_word_count2(STARTING_WC);
}

uint64_t get_word_count(int idx)
{
	return word_list[idx][WORD_COUNT];
}

int get_word_count2(int idx)
{
	return wrdlst[idx].count;
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

void free_word_list()
{
	for (int i = 0; i < GUESSES_ALLOWED; ++i) {
		if (wrdlst[i].words != NULL) {
			free(wrdlst[i].words);
		}
	}
}
