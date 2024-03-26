#ifndef WORDL_WORDS_H
#define WORDL_WORDS_H

void get_guess();
void get_results();


bool is_possible_word(char gs[], char pr[], char tiles[]);

bool issolved(char r[]);

void find_best_word(struct WordScore* pws);


#endif /* WORDL_WORDS_H */
