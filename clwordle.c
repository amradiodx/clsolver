#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h> 
#include "includes.h"
#include "init.h"
#include "verify.h"
#include "words.h"
#include "lists.h"

int mov_num;

uint64_t *words[GUESSES_ALLOWED];
extern char results[TILE_CLR_COMBOS - WORDLEN][WORDBUFSIZE];

struct guess gs[GUESSES_ALLOWED];

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	init();

	bool solved = false;

	do {
		if(mov_num > 0) {
			struct WordScore ms;
			find_best_word(&ms);
			printf("Recommended move is %s with entropy of %.4f\n",
					ms.word, ms.entropy);
		}

		/* Get starting word */
		get_guess();


		/* Get the results */
		get_results();


		/* prospect_word is the word read from wordlist
		   and compared with the guess and tile colors */
		char prospect_word[WORDBUFSIZE];

		for(uint64_t i = 0; i < get_word_count(mov_num); ++i)
		{
			// uint64_t pros = get_word(mov_num, i);
			strncpy(prospect_word, (char*) get_word(mov_num, i), sizeof(prospect_word));

			if(is_possible_word(gs[mov_num].wordpt, 
						 		prospect_word,
								gs[mov_num].tilespt) == true) {
				if(mov_num < (GUESSES_ALLOWED - 1)) {
					add_word(mov_num + 1, prospect_word);
					printf("%s\n", prospect_word);
				}
			}
		}

		if(get_word_count(mov_num + 1) == 1) {
			char str [WORDBUFSIZE];
			// uint64_t wordi = get_word(mov_num + 1, 0);
			strncpy(str, get_word(mov_num + 1, 0), sizeof(str));
			printf("%s is the word!\n", str);
			solved = true;
		}
	} while((++mov_num < GUESSES_ALLOWED) && (solved == false));

	return 0;
}

