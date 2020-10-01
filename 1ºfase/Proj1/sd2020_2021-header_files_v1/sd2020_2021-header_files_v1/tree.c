#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "tree-private.h"
#include "entry.h"

struct tree_t *tree_create()
{
    struct tree_t *created = (struct tree_t *) malloc(sizeof(struct tree_t));
    struct entry_t *value = (struct entry_t *) malloc(sizeof(struct entry_t));
    entry_initialize(value);
    
    created->pair = value;
    created->left = created->right  = NULL;

    return created;
}

void tree_destroy(struct tree_t *tree)
{
    if (tree == NULL) return;

    tree_destroy(tree->right); 
    tree_destroy(tree->left);

    free(tree); 
}

int tree_put(struct tree_t *tree, char *key, struct data_t *value)
{
    if (tree == NULL || key == NULL || value == NULL) return -1;

    char* key_put = (char *) malloc(sizeof(char));
    struct data_t *data_put = (struct data_t *) malloc(sizeof(struct data_t));

    strcpy(key_put,key);
    memcpy(data_put->data,value->data,value->datasize);

    struct entry_t *values = entry_create(key_put,data_put);
    

    struct entry_t *search = tree_get_aux(tree,key_put);
    if(search != NULL)
    {   printf("merda");
        entry_replace(search,key,value);
        return 0;
    }

    if (tree == NULL) 
    {   
        printf("merda1");
        struct tree_t *new_tree = tree_create();
        
    }
    if (entry_compare(values,tree->pair) == -1) 
    {
        printf("merda2");
        tree_put(tree->left, key_put,data_put);
    }
    else if (entry_compare(values,tree->pair) == 1)
    {
        printf("merda3");
        tree_put(tree->right, key_put,data_put);
    }

    return -1;
}

struct data_t *tree_get(struct tree_t *tree, char *key)
{
    struct tree_t * result = tree_clone(tree);
    struct entry_t * aux = (struct entry_t*) malloc(sizeof(struct entry_t));
    entry_initialize(aux);
    char * key_get = (char *) malloc(strlen(key)+1*sizeof(char*));
    strcpy(key_get,key);
    aux->key = key_get;

    if( result->pair != NULL && aux != NULL)
    {
        if(entry_compare(result->pair,aux) == 0) return result->pair->value;

        if(entry_compare(result->left->pair,aux) == -1) return tree_get(result->left, key_get);

        return tree_get(result->right, key_get);
    }
    
    return NULL;
}

struct entry_t *tree_get_aux(struct tree_t *tree, char *key)
{
    struct tree_t * result = tree_clone(tree);
    struct entry_t * aux = (struct entry_t*) malloc(sizeof(struct entry_t));
    entry_initialize(aux);
    char * key_get = (char *) malloc(strlen(key)+1*sizeof(char*));
    strcpy(key_get,key);
    aux->key = key_get;

    if( result->pair != NULL && aux != NULL)
    {
        if(entry_compare(result->pair,aux) == 0) return result->pair;

        if(entry_compare(result->left->pair,aux) == -1) return tree_get_aux(result->left, key_get);

        return tree_get_aux(result->right, key_get);
    }
    
    return NULL;
}

int tree_size(struct tree_t *tree) 
{
  if (tree==NULL || tree->pair->value == NULL) 
  {
    return (0);
  } else 
  {
    return (tree_size(tree->left) + 1 + tree_size(tree->right));
  }
}

int tree_del(struct tree_t *tree, char *key)
{
    struct entry_t *removed = tree_get_aux(tree,key);
    if (removed != NULL) 
    {
        entry_destroy(removed);
        return 0;
    }

    return -1;
}

int tree_height(struct tree_t *tree)
{
    if (tree==NULL) return 0;

    int leftSize = tree_height(tree->left); 
    int rightSize = tree_height(tree->right); 

    if (leftSize > rightSize) return(leftSize+1); 
    else return (rightSize+1);
}

char **tree_get_keys(struct tree_t *tree)
{
    char ** nigger;
    return nigger;
}

void tree_free_keys(char **keys)
{
    return;
}

struct tree_t *tree_clone(struct tree_t *tree)
{
    if (tree == NULL) return NULL;

    struct tree_t* new_tree = tree_create();
    tree_put(new_tree,tree->pair->key,tree->pair->value);

    new_tree->left = tree_clone(new_tree->left);
    new_tree->right = tree_clone(new_tree->right);

    return new_tree;
}