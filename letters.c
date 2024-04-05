#include <stdlib.h>
#include "letters.h"





void
clr_ltrs(letters_t *ltrs)
{
	for (int i = 0; i < LTR_CNT; ++i)
		ltrs->alpha_cnt[i] = 0;
}

int
add_ltr(letters_t *ltrs, char c)
{
	return ++(ltrs->alpha_cnt[c - ASCII_ALPHA_START]);
}

int
get_ltr_cnt(letters_t *ltrs, char c)
{
	return ltrs->alpha_cnt[c - ASCII_ALPHA_START];
}


char
get_ltr(int idx)
{
	return idx + ASCII_ALPHA_START;
}
