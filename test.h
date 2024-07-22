#define DUP "DUP"
#define SLASH '/'
#define PIPE '|'

//hashnode_t* add_node(hashnode_t **tbl, hashnode_t *src);
//void free_node(hashnode_t *node);
int openextwords();
int closewords();

char* getword(char* word);

bool remove_newline(char s []);

int handle_param(void *param, char word[]);
//uint32_t encode_word_hash(char c[]);


#define WORD_CNT 1
#define GET_WORDS 2

