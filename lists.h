#ifndef WORDL_LISTS_H
#define WORDL_LISTS_H

struct wordlist
{
	uint64_t	*words;
	int			count;
	int			alloc_elmnts;
	bool		dup_ltrs;
	uint64_t	blacklist;
};

int init_word_list();
uint64_t get_word_count(int idx);
int get_word_count2(int idx);
uint64_t get_starting_wc();
int get_starting_wc2();
uint64_t get_total_size(int idx);
size_t get_allocated(int idx);
void reset_words();
char *get_word(int guess, int idx);
char *get_word2(int guess, int idx);
int add_word(int guess, char w[]);
int add_word2(int guess, char w[], bool dups);
void free_word_list();

#endif /* WORDL_LISTS_H */
