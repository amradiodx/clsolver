#ifndef WORDL_LISTS_H
#define WORDL_LISTS_H

int init_word_list();
uint64_t get_word_count(int idx);
uint64_t get_starting_wc();
uint64_t get_total_size(int idx);
size_t get_allocated(int idx);
void reset_words();
uint64_t get_word(int guess, int idx);
int add_word(int guess, char w[]);

#endif /* WORDL_LISTS_H */
