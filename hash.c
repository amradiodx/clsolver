#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "includes.h"
#include "hash.h"




uint32_t mask = 0x00003fff;

static int allocated = 0;
static int freed = 0;




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
