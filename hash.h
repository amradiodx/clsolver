#ifndef WORDL_HASH_H
#define WORDL_HASH_H


typedef struct hashnode {
	uint32_t key;
	bool allocated;
	struct hashnode *next_node;
} hashnode_t;
	
hashnode_t* add_node(hashnode_t **tbl, hashnode_t *src);
void free_node(hashnode_t *node);




#endif /* WORDL_HASH_H */
