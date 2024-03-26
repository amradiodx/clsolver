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

extern int mov_num;
extern int word_count;
extern struct moves mov[GUESSES_ALLOWED];

extern uint64_t* words[GUESSES_ALLOWED];

char results[TILE_CLR_COMBOS - WORDLEN][WORDBUFSIZE];

int init()
{
	open_log();

	for(int i = 0; i < GUESSES_ALLOWED; ++i)
	{
		mov[i].guess_word = 0ULL;
		mov[i].tile_rslts = 0ULL;
		mov[i].entropy = 0.0;
		mov[i].gwptr = (char*) &mov[i].guess_word;
		mov[i].trptr = (char*) &mov[i].tile_rslts;
	}
	/* Get possible Wordle answers per character */
	char colors[sizeof(TILE_COLORS)];

	strncpy(colors, TILE_COLORS, sizeof(colors));
	printf("Size of colors is %lu\n", sizeof(colors));
	printf("Size of results[1] is %lu\n", sizeof(results));


	/* Get possible Wordle answers per word */
	const int posresults = power(TILE_COLORS_LEN, WORDLEN); 
	printf("Possible combinations is %d\n", posresults);

	mov_num = 0;
	int offset = 0;
	word_count = 0;
	for(int i = 0; i < posresults; ++i)
	{
		char buf[WORDBUFSIZE];
		strclr(buf, sizeof(buf));

		for(int j = 0; j < 5; ++j)
		{
			buf[j] = colors[(i / power(3, j)) % 3];
		}

		/* Eliminate one yellow and the rest green */
		if(strchrcnt(buf, 'g', sizeof(buf)) == 4 &&
				strchrcnt(buf, 'y', sizeof(buf)) == 1)
		{
			++offset;
			// printf("Color pattern %s to be eliminated\n", buf);
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



		// printf("%d  %s\n", i - offset, buf);
	}

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

	while(getword(buf) != NULL)
	{
		/* Remove newline character */
		remnewln(buf);

		add_word(mov_num, buf);
	}


	if(closewords() != EXIT_SUCCESS)
	{
		printf("Word close error\n");
		return EXIT_FAILURE;
	}

	printf("Word count for index 0 is %lu\n", get_word_count(0));
	atexit(clexit);

	return EXIT_SUCCESS;
}


void clexit()
{
	close_log();

	for(int i = 0; i < GUESSES_ALLOWED; ++i)
	{
		if(words[i] != NULL)
			free(words[i]);
	}

	printf("clexit() called\n");
}
