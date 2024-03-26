#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "includes.h"
#include "words.h"
#include "verify.h"
#include "utils.h"
#include "file.h"
#include "lists.h"


extern struct moves mov[GUESSES_ALLOWED];
extern int mov_num;
extern char results[TILE_CLR_COMBOS - WORDLEN][WORDBUFSIZE];

void get_guess()
{
	do
	{
		printf("\nPlease enter valid word for Guess %d: ", mov_num + 1);
		fgets(mov[mov_num].gwptr, 6, stdin);
		make_lower(mov[mov_num].gwptr);
		printf("Guess is %s\n", mov[mov_num].gwptr);
		char* newln = strrchr(mov[mov_num].gwptr, '\n');
		if(newln == NULL)
		{
			char c = getchar();
			(void) c;
		}	
	} while(verifyword(mov[mov_num].gwptr) == 0);
}

void get_results()
{
	do
	{
		printf("\nPlease entire valid results: ");
		fgets(mov[mov_num].trptr, WORDLEN + 1, stdin);
		make_lower(mov[mov_num].trptr);
		char* newln = strrchr(mov[mov_num].trptr, '\n');
		if(newln == NULL)
		{
			char c = getchar();
			(void) c;
		}
	} while(verifyresults(mov[mov_num].trptr) == 0);
}

bool is_possible_word(char gs[], char pr[], char tiles[])
{
	char prspct[WORDBUFSIZE];
	strncpy(prspct, pr, sizeof(prspct));

	size_t len = strlen(tiles);

	/* First pass processes green letters */
	for(size_t i = 0; i < len; ++i)
	{
		if(TILE_GREEN == tiles[i]) 
		{
			if(prspct[i] == gs[i])
			{
				prspct[i] = '*';
			}
			else
			{
				return false;
			}
		}
		else
		{
			if(prspct[i] == gs[i])
			{
				return false;
			}
		}
	}

	/* Second pass processes yellow letters */
	for(size_t i = 0; i < len; ++i)
	{
		if(TILE_YELLOW == tiles[i])
		{
			char* c = strchr(prspct, gs[i]);
			if(c == NULL)
			{
				return false;
			}
			else
			{
				*c = '*';
			}
		}
	}

	/* Third pass processes gray letters */
	for(size_t i = 0; i < len; ++i)
	{
		if(TILE_GRAY == tiles[i])
		{
			char* c = strchr(prspct, gs[i]);
			if(c != NULL)
			{
				return false;
			}
		}
	}
	return true;
}

 

bool issolved(char r[])
{
	return strncmp(r, SOLVED, strlen(SOLVED)) == 0;
}

void find_best_word(struct WordScore* pws)
{
	memset(pws, '\0', sizeof(struct WordScore));

	/* Loop through entire wordlist */
	for(uint64_t i = 0; i < get_word_count(0); ++i)
	{
		int entropy_count = 0;
		float entropy = 0.0;
		char gw[WORDBUFSIZE];
		uint64_t wordi = get_word(0, i);
		strncpy(gw, (char*) &wordi, sizeof(gw));
		
		/* Loop through all tile color combinations */
		for(uint64_t j = 0; j < TILE_CLR_COMBOS - WORDLEN; ++j)
		{
			char c[WORDBUFSIZE];
			uint64_t wc = 0;
			/* Loop through narrowed down list of possible words */
			for(uint64_t k = 0; k < get_word_count(mov_num); ++k)
			{
				uint64_t word = get_word(mov_num, k);
				strncpy(c, (char*) &word, sizeof(c));
				if(is_possible_word(gw, c, results[j]))
				{
					++wc;
				}
			}
			
			if(wc > 0)
			{
				++entropy_count;
				float buf = get_entropy((float) wc, (float) get_word_count(mov_num)); 
				entropy += buf;
			}
		}
		char log_buf[256];
		sprintf(log_buf, "Guess %s entropy is %.4f-- tile combo count is %d\n", gw, entropy, entropy_count );
				log_entry(log_buf);
		
		if(entropy >= pws->entropy)
		{
			pws->entropy = entropy;
			strncpy(pws->word, gw, WORDBUFSIZE);
			// printf("Entropy return for %s is %.5f\n", pws->word, pws->entropy);
		}
	}
}
