#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sqlite3.h>

#include "includes.h"
#include "database.h"


sqlite3 *db = NULL;

static int callback(void *param, int argc, char **argv, char ** /* azColName */) {
	for (int i = 0; i < argc; i++) {
		// printf("%s\n", argv[i] ? argv[i] : "NULL");
	}
	// printf("\n");
	if (param == NULL) return 1;
	handle_param(param, *argv);
	return 0;
}

int handle_param(void *param, char word[])
{
	uint64_t disp = *((uint64_t*) param);

	switch (disp) {
		case WORD_CNT: {
		   	char *dst = NULL;
		   	uint64_t ret = strtol(word, &dst, 10);
			if (dst == NULL || *dst != '\0') return 1;
			struct word_count *wc = (struct word_count*) param;
			wc->count = ret;
			break;
		}

		case GET_WORDS: {
			struct get_words *gw = (struct get_words*) param;
			strncpy(TO_CHAR(gw->words[gw->iterator++]), word, sizeof(uint64_t));
			break;
		}

		default:
			return 1;
	}
	return 0;
}


int open_db(const char* words_db)
{
	int rc = sqlite3_open(words_db, &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}
	return rc;	
}


int exec_db(const char *sql, void *arg) {
	char *err_msg = 0;
	int rc = sqlite3_exec(db, sql, callback, arg, &err_msg); 
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return -1;
	}
	return 0;
}

int close_db()
{
	return sqlite3_close(db);
}

int exec_sql(void* /* param */, char *sql_select, char *sql_from,
			char *sql_where, char *sql_orderby)
{
	if (sql_select == NULL || sql_from == NULL) return 1;
	char *semicolon = ";";
	char *space = " ";
	char sql[1024];
	strncpy(sql ,sql_select, sizeof(sql) - 1);
	strncat(sql, space, sizeof(sql) - 1);
	strncat(sql, sql_from, sizeof(sql) - 1);

	if (sql_where != NULL) {
		strncat(sql, space, sizeof(sql) -1);
		strncat(sql, sql_where, sizeof(sql) - 1);
	}

	if (sql_orderby != NULL) {
		strncat(sql, space, sizeof(sql) - 1);
		strncat(sql, sql_orderby, sizeof(sql) - 1);
	}

	strncat(sql, semicolon, sizeof(sql) - 1);
	

	return 0;
}
