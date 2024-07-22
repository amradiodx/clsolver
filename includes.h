#ifndef WORDL_INCLUDES_H
#define WORDL_INCLUDES_H


/* Length of Wordle word */
#define WORDLEN 5

/* Size of word buffer */
#define WORDBUFSIZE WORDLEN + 1
#define GUESSES_ALLOWED 6

/* Possible results for each letter; g, y, or none */
#define TILE_GREEN 'g'
#define TILE_YELLOW 'y'
#define TILE_GRAY '-'

#define TILE_COLORS "-yg" 
#define TILE_COLORS_LEN 3
#define TILE_CLR_COMBOS 243 // 3 ^ 5

#define BLOCK_SIZE 100

#define WORDFILE	"wordlist%d.txt"
#define LOGFILE		"clsolver.log"
#define WORDS_EXT	"words-ext.txt"
#define SOLVED 		"ggggg"

#define TO_CHAR(n) ((char*) (&n))
#define WORDS_DB	"clsolver.db"

struct word_list {
	uint64_t word;
};
struct WordScore
{
	char word[WORDBUFSIZE];
	float entropy;
};

struct guess
{
	char   	word[WORDBUFSIZE];
	char	tiles[WORDBUFSIZE];
};

struct duplicates
{
	int count;
	int locations[4];
};

#endif /* WORDL_INCLUDES_H */
