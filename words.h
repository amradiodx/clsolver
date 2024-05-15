#ifndef WORDL_WORDS_H
#define WORDL_WORDS_H

void init_word_hash();
uint32_t encode_word_hash(char c[]);
uint32_t test_word_hash(char c[], uint32_t h);
void get_guess(char *dflt);
void get_results();
bool is_possible_word(char gs[], char pr[], char tiles[]);
void find_best_word(struct WordScore* pws);
int handle_multiples(char *word, struct duplicates *dupes);
bool skip_tiles(char *tiles, struct duplicates *dupes, int cnt);

#endif /* WORDL_WORDS_H */
