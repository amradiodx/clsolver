#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "includes.h"
#include "init.h"
#include "utils.h"
#include "file.h"
#include "lists.h"
#include "letters.h"
#include "words.h"

extern int mov_num;
extern struct guess gs[GUESSES_ALLOWED];

char results[TILE_CLR_COMBOS - WORDLEN][WORDBUFSIZE];

int
init()
{
	open_log();

	for(int i = 0; i < GUESSES_ALLOWED; ++i) {
		gs[i].word 		= 0ULL;
		gs[i].tiles 	= 0ULL;
		gs[i].wordpt	= (char*) &gs[i].word;
		gs[i].tilespt	= (char*) &gs[i].tiles;
	}
	/* Get possible Wordle answers per character */
	char colors[sizeof(TILE_COLORS)];

	strncpy(colors, TILE_COLORS, sizeof(colors));


	/* Get possible Wordle answers per word */
	const int posresults = power(TILE_COLORS_LEN, WORDLEN); 

	mov_num = 0;
	int offset = 0;
	for(int i = 0; i < posresults; ++i) {
		char buf[WORDBUFSIZE];
		strclr(buf, sizeof(buf));

		for(int j = 0; j < 5; ++j)
			buf[j] = colors[(i / power(3, j)) % 3];

		/* Eliminate one yellow and the rest green */
		if(strchrcnt(buf, 'g', sizeof(buf)) == 4 &&
				strchrcnt(buf, 'y', sizeof(buf)) == 1) {
			++offset;
			continue;
		}

		strncpy(results[i - offset], buf, sizeof(results[i - offset])); 
		
		int k = WORDLEN;
		for(int j = 0; j < (WORDLEN / 2); ++j)
		{
			char c = buf[j];
			buf[j] = buf[--k];
			buf[k] = c;
		}
	}

	init_word_hash();

	if(init_word_list() != EXIT_SUCCESS)
	{
		printf("Wordlist initialization failure\n");
		return EXIT_FAILURE;
	}

	if(openwords() != EXIT_SUCCESS)
	{
		printf("Word open error\n");
		return EXIT_FAILURE;
	}


	char buf[WORDBUFSIZE];

	while(getword(buf, sizeof(buf)) != NULL) {
		remove_newline(buf);

		// bool dupes = has_mult_ltrs(buf);
		// add_word(mov_num, buf);
		add_word(mov_num, buf /*, dupes*/ );
		uint32_t hash = encode_word_hash(buf);
		uint32_t test = test_word_hash(buf, hash);
/*
		if (dupes == true) {
			letters_t ltrs;
			clr_ltrs(&ltrs);
			struct duplicates dupes;
			init_dupes(&dupes);
			printf("Word with dupes is %s", buf);
			for (int i = 0; i < WORDLEN; ++i) {
				add_ltr(&ltrs, buf[i]);
			}
			for (int i = 0; i < LTR_CNT; ++i) {
				int cnt = get_ltr_cnt(&ltrs, get_ltr(i));
				if (cnt > 1) {
					printf("  %c %d", get_ltr(i), cnt);
				}
			}
			printf("\n");
		} */
	}


	if(closewords() != EXIT_SUCCESS) {
		printf("Word close error\n");
		return EXIT_FAILURE;
	}

	atexit(clexit);

	return EXIT_SUCCESS;
}

void
get_char_locs(char str[], char c, size_t size, struct duplicates *dupes)
{
	dupes->letter = c;
	for(size_t i = 0; i < size; ++i) {
		if(str[i] == c) {
			dupes->locations[dupes->count++] = i;
			str[i] = '*';
		}
	}
}



void
clexit()
{
	free_word_list();
	close_log();
}
