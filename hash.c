#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "includes.h"
#include "hash.h"
#include "letters.h"




uint32_t mask = 0x00003fff;

static int allocated = 0;
static int freed = 0;


uint32_t word_hash[WORDLEN * LTR_CNT];


uint32_t
get_word_hash(const int i)
{
	return word_hash[i];
}


void
init_word_hash()
{
	for (int i = 0; i < WORDLEN * LTR_CNT; ++i) {
		word_hash[i] = arc4random_uniform(RAND_MAX);
	}
}

uint32_t
encode_word_hash(char c[])
{
	uint32_t hash = 0;
	for (int i = 0; i < WORDLEN; ++i) {
		int idx = i * LTR_CNT + get_ltr_idx(c[i]);
		hash ^= word_hash[idx];
	}

	return hash;
}


uint32_t
test_word_hash(char c[], uint32_t h)
{
	uint32_t hash = h;
	for (int i = 0; i < WORDLEN; ++i) {
		int idx = i * LTR_CNT + get_ltr_idx(c[i]);
		hash ^= word_hash[idx];
	}

	return hash;
}



hashnode_t*
add_node(hashnode_t **tbl, hashnode_t *src)
{
	static int max_depth;
	int depth = 0;
	uint32_t idx = src->key & mask;
	if (tbl[idx] == NULL) {
		tbl[idx] = (hashnode_t*) calloc(sizeof(hashnode_t), 1);
		(*(tbl + idx))->key = src->key;
		assert(tbl[idx]->allocated == false);
		tbl[idx]->allocated = true;
		++allocated;
		return tbl[idx];
	}

	hashnode_t *node = tbl[idx];
	while (node->next_node != NULL) {
		node = node->next_node;
		++depth;
	}
	if(depth > max_depth) {
		max_depth = depth;
		printf("Depth has reached %d\n", max_depth);
	}
	node->next_node = (hashnode_t*) calloc(sizeof(hashnode_t), 1);
	assert(node->next_node->allocated == false);
	node->next_node->allocated = true;
	node->next_node->key = src->key;
	++allocated;
	return node->next_node;
}

void
free_node(hashnode_t *node)
{
	if(node == NULL)
		return;

	if (node->next_node != NULL) {
		free_node(node->next_node);
	}
	assert(node->allocated == true);
	free(node);
	++freed;
}
