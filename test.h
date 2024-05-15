
typedef struct hashnode {
	uint32_t key;
	char word[WORDBUFSIZE];
	bool allocated;
	struct hashnode *next_node;
} hashnode_t;
	
hashnode_t* add_node(hashnode_t **tbl, hashnode_t *src);
void free_node(hashnode_t *node);
int openextwords();
int closewords();

char* getword(char* word);

bool remove_newline(char s []);

uint32_t encode_word_hash(char c[]);

hashnode_t* locate_word(char word[]);

