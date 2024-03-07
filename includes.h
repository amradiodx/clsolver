
/* Length of Wordle word */
#define CLWSTRLEN 5

/* Possible results for each letter; g, y, or none */
#define LTRRESULTS "-yg" 
#define LTRRESULTSLEN 3
#define WORDFILE "wordlist%d.txt"
#define SOLVED "ggggg"

/* Possible results for each word */
#define POSSRESULTS (LTRRESULTS ^ CLWSTRLEN)

struct cntarray
{
	short idx;
	char ar[CLWSTRLEN + 1];
};
