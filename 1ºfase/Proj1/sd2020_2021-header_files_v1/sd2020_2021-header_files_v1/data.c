#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

struct data_t *data_create(int size) 
{
    struct data_t * pcreated;
    if (size<=0)
		return NULL;
    
    pcreated = (struct data_t *) malloc(sizeof(struct data_t));

    if (pcreated == NULL)
    {
        free(pcreated);
	    return NULL;
	}

    pcreated -> data = malloc(size);

    if (pcreated -> data == NULL)
    {
		free(pcreated);
        return NULL;
	}
    pcreated -> datasize = size;
    return pcreated;
};

struct data_t *data_create2(int size, void *data){
    struct data_t * pcreated;
    if (size<=0) return NULL;
    
    pcreated = (struct data_t *) malloc(sizeof(struct data_t));

    if (pcreated == NULL)
    {
        free(pcreated);
	    return NULL;
	}

    pcreated -> data = data;
    
    if (pcreated -> data == NULL)
    {
		free(pcreated);
        return NULL;
	}
    pcreated -> datasize = size;
    return pcreated;
}

void data_destroy(struct data_t *data)
{
    if (data != NULL)
    {
		if(data -> data != NULL)
        {
			free(data -> data);
		}
	}     
    free (data);
}


struct data_t *data_dup(struct data_t *data)
{
    if ((data == NULL) ||  (data->data == NULL) || (data ->datasize <= 0)) return NULL;
    struct data_t *dup = data_create(data->datasize);
    if ((dup == NULL) || (dup->data == NULL)) return NULL;
    memcpy(dup -> data, data -> data, data -> datasize);
    return dup;
}

void data_replace(struct data_t *data, int new_size, void *new_data)
{
    // if ((data == NULL) ||  (data->data == NULL) || (data ->datasize <= 0)) return NULL;
    // if((new_data == NULL) || (new_size)<=0) return NULL;
    data->data = new_data;
    data->datasize = new_size;
}