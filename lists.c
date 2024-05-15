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



struct wordlist wrdlst[GUESSES_ALLOWED];

int
init_word_list()
{
	for(int i = 0; i < GUESSES_ALLOWED; ++i)
	{
		wrdlst[i].alloc_elmnts = BLOCK_SIZE;
		wrdlst[i].words_ = (uint64_t*) malloc(BLOCK_SIZE * sizeof(uint64_t));
		if(wrdlst[i].words_ == NULL)
		{
			printf("word_list allocation failed!\n");
			return EXIT_FAILURE;
		}
		wrdlst[i].count = 0;
	}
	return EXIT_SUCCESS;
}


char 
*get_word(int guess, int idx)
{
	return (char*) &wrdlst[guess].words_[idx];
}

int
add_word(int guess, char w[] /*, bool dups */)
{
	uint64_t *words = wrdlst[guess].words_;
	if (wrdlst[guess].count >= wrdlst[guess].alloc_elmnts) {
		wrdlst[guess].alloc_elmnts += BLOCK_SIZE;
		wrdlst[guess].words_ = realloc(wrdlst[guess].words_,
				sizeof(uint64_t) * wrdlst[guess].alloc_elmnts);
		words = wrdlst[guess].words_;
	}

	strncpy((char*) &words[wrdlst[guess].count++], w, sizeof(uint64_t));

	return wrdlst[guess].count;
}


int
get_starting_wc()
{
	return get_word_count(STARTING_WC);
}

uint64_t
get_word_count(int idx)
{
	return wrdlst[idx].count;
}


size_t
get_allocated(int idx)
{
	return wrdlst[idx].alloc_elmnts;
}

void
free_word_list()
{
	for (int i = 0; i < GUESSES_ALLOWED; ++i) {
		if (wrdlst[i].words_ != NULL) {
			free(wrdlst[i].words_);
		}
	}
}
