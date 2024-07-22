#ifndef WORDL_WORDS_H
#define WORDL_WORDS_H


bool cb_input_filter(char c);

void get_input(char word[], int length, bool (*pf)(char));
void get_guess(char *dflt);
void get_results();
bool check_green1(char gs[], char pr[], char tiles[]);
bool check_green2(char gs[], char pr[], char tiles[]);
bool is_possible_word(char gs[], char pr[], char tiles[]);
void find_best_word(struct WordScore* pws);
int handle_multiples(char *word, struct duplicates *dupes);
bool skip_tiles(char *tiles, struct duplicates *dupes, int cnt);

#endif /* WORDL_WORDS_H */
