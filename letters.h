#ifndef WORDL_LETTERS_H
#define WORDL_LETTERS_H

#define LTR_CNT 26
#define ASCII_ALPHA_START 97 /* Lowercase offset */

typedef int letters_t[LTR_CNT];

void clr_ltrs(letters_t *ltrs);
int add_ltr(letters_t *ltrs, char c);
int get_ltr_cnt(letters_t *ltrs, char c);
char get_ltr(int idx);

#endif /* WORDL_LETTERS_H */