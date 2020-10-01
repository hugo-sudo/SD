#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "entry.h"

struct entry_t *entry_create(char *key, struct data_t *data)
{
    struct entry_t *created = (struct entry_t*) malloc(sizeof(struct entry_t));
    if ((data == NULL) ||  (data->data == NULL) || (data ->datasize <= 0) || (key == NULL)) return NULL;
    created->key = key;
    created->value  = data;
    
    return created;
}

void entry_initialize(struct entry_t *entry)
{
    entry->key = NULL;
    entry->value = NULL;
}

void entry_destroy(struct entry_t *entry)
{
    free(entry);
}


struct entry_t *entry_dup(struct entry_t *entry) 
{   
    if (entry->key != NULL && entry->value != NULL) 
    {
        struct entry_t *dup = entry_create (strdup(entry -> key), data_dup(entry -> value));
        return dup;
    }
    
}

void entry_replace(struct entry_t *entry, char *new_key, struct data_t *new_value)
{
    free(entry->key);
    free(entry->value);

    entry->key = new_key;
    entry->value = new_value;

}

int entry_compare(struct entry_t *entry1, struct entry_t *entry2)
{   
    struct entry_t * first = entry_dup(entry1);
    struct entry_t * second = entry_dup(entry2);

    if (first != NULL && second != NULL) 
    {
        if (strcmp(first->key,second->key) > 0)
        {   
            return 1;
        }

        if (strcmp(first->key,second->key) < 0)
        {
            return -1;
        }
    
        return 0;
    }
    
}