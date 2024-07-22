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
#include "database.h"

extern int mov_num;
extern struct guess gs[GUESSES_ALLOWED];

char results[TILE_CLR_COMBOS - WORDLEN][WORDBUFSIZE];

int
init()
{
	open_log();

	for(int i = 0; i < GUESSES_ALLOWED; ++i) {
		strclr(gs[i].word, WORDBUFSIZE);
		strclr(gs[i].tiles, WORDBUFSIZE);
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

	if(init_word_list() != EXIT_SUCCESS)
	{
		printf("Wordlist initialization failure\n");
		return EXIT_FAILURE;
	}

	int rc = open_db(WORDS_DB);
	if(rc) {
		return rc;
	}	

	struct get_words gw;
	memset(&gw, 0, sizeof(gw));
	gw.sql_dispatch = GET_WORDS;
	char* sql2  = "SELECT word FROM words WHERE solution = TRUE ORDER BY word;";
	rc = exec_db(sql2, &gw);
	if (rc != 0) {
		close_db();
		return EXIT_FAILURE;
	}

	for (int i = 0; i < gw.iterator; ++i)
	{
		add_word(mov_num, TO_CHAR(gw.words[i]) /*, dupes*/ );
	}

	close_db();

	atexit(clexit);

	return EXIT_SUCCESS;
}


void
clexit()
{
	free_word_list();
	close_log();
}
