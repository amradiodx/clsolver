#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "includes.h"
#include "words.h"
#include "verify.h"
#include "utils.h"
#include "file.h"
#include "lists.h"
#include "letters.h"


extern struct guess gs[GUESSES_ALLOWED];
extern int mov_num;
extern char results[TILE_CLR_COMBOS - WORDLEN][WORDBUFSIZE];

void
get_guess(char *dflt)
{
	do {
		if (mov_num == 0) {
		printf("\nPlease enter valid word for Guess %d: ", mov_num + 1);
		} else {
			printf("\nPlease enter valid word for Guess %d <RETURN to use %s>: ", mov_num + 1, dflt);
		}
		fgets(gs[mov_num].wordpt, 6, stdin);
		make_lower(gs[mov_num].wordpt);
		if(mov_num != 0 && strlen(gs[mov_num].wordpt) == 1) {
			strncpy(gs[mov_num].wordpt, dflt, WORDBUFSIZE);
		}
		printf("Guess is %s\n", gs[mov_num].wordpt);
		fpurge(stdin);
		/*char* newln = strrchr(gs[mov_num].wordpt, '\n');
		if(newln == NULL) {
			char c = getchar();
			(void) c;
		}*/
	} while(verifyword(gs[mov_num].wordpt) == 0);
}

void
get_results()
{
	do {
		printf("\nPlease entire valid results: ");
		fgets(gs[mov_num].tilespt, WORDLEN + 1, stdin);
		make_lower(gs[mov_num].tilespt);
		char* newln = strrchr(gs[mov_num].tilespt, '\n');
		if(newln == NULL) {
			char c = getchar();
			(void) c;
		}
	} while(verifyresults(gs[mov_num].tilespt) == 0);
}

bool
is_possible_word(char gs[], char pr[], char tiles[])
{
	char prspct[WORDBUFSIZE];
	strncpy(prspct, pr, sizeof(prspct));

	size_t len = strlen(tiles);

	/* First pass processes green letters */
	for(size_t i = 0; i < len; ++i) {
		if(TILE_GREEN == tiles[i]) { 
			if(prspct[i] == gs[i]) {
				prspct[i] = '*';
			}
			else {
				return false;
			}
		}
		else {
			if(prspct[i] == gs[i]) {
				return false;
			}
		}
	}

	/* Second pass processes yellow letters */
	for(size_t i = 0; i < len; ++i) {
		if(TILE_YELLOW == tiles[i]) {
			char* c = strchr(prspct, gs[i]);
			if(c == NULL) {
				return false;
			}
			else {
				*c = '*';
			}
		}
	}

	/* Third pass processes gray letters */
	for(size_t i = 0; i < len; ++i) {
		if(TILE_GRAY == tiles[i]) {
			char* c = strchr(prspct, gs[i]);
			if(c != NULL) {
				return false;
			}
		}
	}

	return true;
}



void
find_best_word(struct WordScore* pws)
{
	memset(pws, '\0', sizeof(struct WordScore));

	/* Loop through entire wordlist */
	for(uint64_t i = 0; i < get_word_count(0); ++i)
	{
		float entropy = 0.0;
		uint64_t wcmax = 0;
		char gw[WORDBUFSIZE];
		struct duplicates dupes[2];
		memset(dupes, 0, sizeof(dupes));
		strncpy(gw, get_word(0, i), sizeof(gw));

		int mults = handle_multiples(gw, dupes);
		int counter = mults;
	
		/* Loop through all tile color combinations */
		for (uint64_t j = 0; j < TILE_CLR_COMBOS - WORDLEN; ++j) {
			char c[WORDBUFSIZE];
			uint64_t wc = 0;
			
			char rslts[WORDBUFSIZE];
			strncpy(rslts, results[j], sizeof(rslts));
			if (skip_tiles(rslts, dupes, counter)) {
				// printf("Pattern %s skipped for %s\n", results[j], gw);
				continue;
			}
			
			/* Loop through narrowed down list of possible words */
			for(uint64_t k = 0; k < get_word_count(mov_num); ++k) {
				strncpy(c, get_word(mov_num, k), sizeof(c));
				if(is_possible_word(gw, c, results[j])) {
					++wc;
				}
			}
			
			if(wc > 0)
			{
				if(wc > wcmax) {
					wcmax = wc;
				}
				float buf = get_entropy((float) wc, (float) get_word_count(mov_num));
				entropy += buf;
			}
		}
		char log_buf[256];
		sprintf(log_buf, "Guess %s entropy is %.4f-- max word count is %lu\n", gw, entropy, wcmax);
				log_entry(log_buf);
		
		if(entropy > pws->entropy) {
			pws->entropy = entropy;
			strncpy(pws->word, gw, WORDBUFSIZE);
			// printf("Entropy return for %s is %.5f\n", pws->word, pws->entropy);
		}
	}
}



int
handle_multiples(char *word, struct duplicates *dupes)
{
	int mult_count = 0;
	letters_t ltrs;
	clr_ltrs(&ltrs);
	for (size_t i = 0; i < strnlen(word, WORDLEN); ++i)
		add_ltr(&ltrs, word[i]);

	for(int i = 0; i < LTR_CNT; ++i)
		if (ltrs.alpha_cnt[i] > 1) {
			int loc_idx = 0;
			dupes[mult_count].letter = get_ltr(i);
			for (int k = 0; k < WORDLEN; ++k) {
				if(dupes[mult_count].letter == word[k])
					dupes[mult_count].locations[loc_idx++] = k;
			}
			dupes[mult_count].count = loc_idx;
			++mult_count;
		}

	return mult_count;
}


bool
skip_tiles(char *tiles, struct duplicates *dupes, int cnt)
{
	bool gray_tile_found = false;
	while (cnt--) {
		for (int i = 0; i < dupes[cnt].count; ++i) {
			if(gray_tile_found == true && 
				tiles[dupes[cnt].locations[i]] == 'y') {
				return true;
			}
			if (gray_tile_found == false &&
				tiles[dupes[cnt].locations[i]] == '-') {
				gray_tile_found = true;
			}
		}
	}
	return false;
}
