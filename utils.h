#ifndef WORDL_UTILS_H
#define WORDL_UTILS_H





void make_lower(char s[]);

int power(int x, int n);

void strclr(char str[], size_t size);

int add_char_to_string(char str[], char c, size_t size);


void str_intrsct(const char str1[], const char str2[], char rslt[], size_t rslt_size);


bool has_mult_ltrs(char s[]);

void init_dupes(struct duplicates *dupes);

int strchrcnt(char str[], char c, size_t size);


float get_entropy(unsigned int word_count, unsigned int total_words);
float get_entropy2(unsigned int word_count, unsigned int total_words);



#endif /* WORDL_UTILS_H */
