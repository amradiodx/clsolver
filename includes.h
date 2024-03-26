#ifndef WORDL_INCLUDES_H
#define WORDL_INCLUDES_H


/* Length of Wordle word */
#define WORDLEN 5
#define WORDBUFSIZE WORDLEN + 2
#define GUESSES_ALLOWED 6

/* Possible results for each letter; g, y, or none */
#define TILE_GREEN 'g'
#define TILE_YELLOW 'y'
#define TILE_GRAY '-'

#define TILE_COLORS "-yg" 
#define TILE_COLORS_LEN 3
#define TILE_CLR_COMBOS 243 // 3 ^ 5

#define BLOCK_SIZE 100

#define WORDFILE "wordlist%d.txt"
#define LOGFILE "clwordle.log"
#define SOLVED "ggggg"

/* Possible results for each word */
// #define POSSRESULTS (TILE_COLORS_LEN ^ WORDLEN)

struct WordScore
{
	char word[WORDBUFSIZE];
	float entropy;
};

struct moves
{
	uint64_t guess_word;
	char* gwptr;
	uint64_t tile_rslts;
	char* trptr;
	float entropy;
};

#endif /* WORDL_INCLUDES_H */
