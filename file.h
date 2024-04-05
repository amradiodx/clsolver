#ifndef WORDL_FILE_H
#define WORDL_FILE_H


int initwords(char* wordfile);

int open_log();
int close_log();
int log_entry(char log[]);

int openwords();
// int openwwords();
void clrewind();

// int rdwrdlst();
char* getword(char* word);
// int putword(char* word);

int closewords();
// int closewwords();



#endif /* WORDL_FILE_H */
