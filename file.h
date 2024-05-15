#ifndef WORDL_FILE_H
#define WORDL_FILE_H


int initwords(char* wordfile);

int open_log();
int close_log();
int log_entry(char log[]);

int openwords();
void clrewind();

char* getword(char* word, size_t size);

int closewords();



#endif /* WORDL_FILE_H */
