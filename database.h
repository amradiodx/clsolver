#ifndef WORDL_DATABASE_H
#define WORDL_DATABASE_H

#define WORD_CNT 1
#define GET_WORDS 2


struct word_count
{
	uint64_t sql_dispatch;
	char *sql_command;
	int count;
};

struct get_words
{
	uint64_t sql_dispatch;
	uint64_t words[2400];
	int iterator;
};


// static int callback(void *param, int argc, char **argv, char **azColName);
int handle_param(void *param, char word[]);

int open_db(const char* db);
int exec_sql(void *param, char *sql_select, char *sql_from, 
			char *sql_where, char *sql_orderby);

int exec_db(const char *sql, void *arg);
int close_db();

#endif /* WORDL_DATABASE_H */
