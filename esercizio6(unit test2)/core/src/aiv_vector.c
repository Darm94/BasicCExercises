#include "aiv_vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void aiv_vector_init(aiv_vector_t* vector, size_t item_size){
    vector->items = NULL;
    vector->item_size=item_size;
    vector->count=0;
    
}

void aiv_vector_free(aiv_vector_t* vector){
    free(vector->items);
    vector->items = NULL;
    vector->item_size=0;
    vector->count=0;
    
}

void aiv_vector_add(aiv_vector_t* vector,void* item){
    size_t new_count = vector->count+1;
    vector->items = realloc(vector->items,vector->item_size * new_count);
    //memcpy(vector->items,item,vector->item_size);//va cambiato perhcè roba vecchia copiata dal realloc
    //ma va messa la parte nuova
    uint8_t* mem_dest = (uint8_t *)vector->items + (vector->item_size * vector->count);
    memcpy(mem_dest,item,vector->item_size);
    vector->count=new_count;
}

void * aiv_vector_get(aiv_vector_t* vector, size_t index){
    return (uint8_t *)vector->items + (vector->item_size * index);
}