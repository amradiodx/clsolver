#ifndef WORDL_HASH_H
#define WORDL_HASH_H


typedef struct hashnode {
	uint32_t key;
	char word[WORDBUFSIZE];
	bool allocated;
	struct hashnode *next_node;
} hashnode_t;
	
void init_word_hash();
uint32_t encode_word_hash(char c[]);
uint32_t test_word_hash(char c[], uint32_t h);
uint32_t get_word_hash(int i);
hashnode_t* add_node(hashnode_t **tbl, hashnode_t *src);
void free_node(hashnode_t *node);
hashnode_t* locate_word(char word[]);



#endif /* WORDL_HASH_H */
