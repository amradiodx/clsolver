#ifndef WORDL_LISTS_H
#define WORDL_LISTS_H

int init_word_list();
_ulonglong get_word_count(int idx);
size_t get_allocated(int idx);
void reset_words();
_ulonglong get_word(int idx);
int add_word(int guess, char w[]);

#endif /* WORDL_LISTS_H */
