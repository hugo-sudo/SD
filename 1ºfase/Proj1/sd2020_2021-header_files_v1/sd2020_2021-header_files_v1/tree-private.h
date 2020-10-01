#ifndef _TREE_PRIVATE_H
#define _TREE_PRIVATE_H

#include "tree.h"

struct tree_t {
	struct entry_t *pair;
	struct tree_t *left; 
	struct tree_t *right; 
};

struct entry_t *tree_get_aux(struct tree_t *tree, char *key);

struct tree_t *tree_clone(struct tree_t *tree);
#endif
