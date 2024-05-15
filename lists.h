#ifndef WORDL_LISTS_H
#define WORDL_LISTS_H


struct wordlist
{
	uint64_t	*words_;
	uint64_t	count;
	uint64_t	alloc_elmnts;
};

int init_word_list();
uint64_t get_word_count(int idx);
int get_starting_wc();
size_t get_allocated(int idx);
void reset_words();
char *get_word(int guess, int idx);
int add_word(int guess, char w[] /*, bool dups */);
void free_word_list();

#endif /* WORDL_LISTS_H */
