#include "aiv_dict.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Bernstein classic hash
static size_t djb33x_hash(void *key, size_t keylen) {
    register int hash = 5381;
    int i;

    unsigned char *key_as_num = (unsigned char *)key;

    for (i = 0; i < keylen; i++) {
        hash = ((hash << 5) + hash) ^ key_as_num[i];
    }

    return hash;
}

aiv_dict_t aiv_dict_new() {
    return aiv_dict_new_with_params(10, djb33x_hash);
}

aiv_dict_t aiv_dict_new_with_params(size_t hashmap_size, size_t (*hash_func)(void *key, size_t keylen)) {
    aiv_dict_t dict;
    dict.hashmap_size = hashmap_size;
    dict.hash_func = hash_func;
    dict.hashmap = (void**)calloc(dict.hashmap_size, sizeof(void*));//my fix: there was not an allocation
    dict.items_count = 0;//my add
    return dict;
}
void aiv_dict_put(aiv_dict_t* dict, void* key, size_t key_size, void* value) {
    size_t hash = dict->hash_func(key, key_size);//fix now it have to be more generic
    size_t hash_index = hash % dict->hashmap_size;

    // Case1: hash(key) not exist
    if (!dict->hashmap[hash_index]) {
        aiv_dict_node_t* node = malloc(sizeof(aiv_dict_node_t));
        node->key = malloc(key_size);
        memcpy(node->key, key, key_size);
        node->key_size = key_size;
        node->value = value;
        node->next = NULL;

        dict->hashmap[hash_index] = node;
        dict->items_count++;
    } else {
        // Case 2: hash(key) exist
        aiv_dict_node_t* node = dict->hashmap[hash_index];
        aiv_dict_node_t* last = NULL;

        while (node) {
            last = node;

            // If key exist, update value
            if (node->key_size == key_size && memcmp(node->key, key, key_size) == 0) {
                node->value = value;
                return;
            }

            node = node->next;
        }

        // If does not exist, add a new node on tail
        aiv_dict_node_t* new_node = malloc(sizeof(aiv_dict_node_t));
        new_node->key = malloc(key_size);
        memcpy(new_node->key, key, key_size);
        new_node->key_size = key_size;
        new_node->value = value;
        new_node->next = NULL;

        last->next = new_node;
        dict->items_count++;
    }

    
}

// GET 
void* aiv_dict_get(aiv_dict_t* dict, void* key, size_t key_size) {
    size_t hash = dict->hash_func(key, key_size);
    size_t hash_index = hash % dict->hashmap_size;

    aiv_dict_node_t* node = dict->hashmap[hash_index];
    while (node) {
        //key match
        if (node->key_size == key_size && memcmp(node->key, key, key_size) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

// CONTAINS 
bool aiv_dict_contains_key(aiv_dict_t* dict, void* key, size_t key_size) {
    return aiv_dict_get(dict, key, key_size) != NULL;
}

/* REMOVE: return true if element removed, false not found */
bool aiv_dict_remove(aiv_dict_t* dict, void* key, size_t key_size) {
    size_t hash = dict->hash_func(key, key_size);
    size_t hash_index = hash % dict->hashmap_size;

    aiv_dict_node_t* node = dict->hashmap[hash_index];
    aiv_dict_node_t* prev = NULL;

    while (node) {
        //key match
        if (node->key_size == key_size && memcmp(node->key, key, key_size) == 0) {
            if (prev) prev->next = node->next;//not first element
            else      dict->hashmap[hash_index] = node->next;//first element

            free(node->key);
            free(node);
            dict->items_count--;
            return true;
        }
        //node scroll
        prev = node;
        node = node->next;
    }
    return false;
}

// SIZE 
size_t aiv_dict_get_size(aiv_dict_t* dict) {
    return dict->items_count;
}
size_t aiv_dict_get_hashmap_elements_size(aiv_dict_t* dict) {
    return dict->hashmap_size;
}

//DESTROY: free hashmap elements called bucket and nodes
void aiv_dict_destroy(aiv_dict_t* dict) {
    if (!dict || !dict->hashmap) return;

    //Select All buckets
    for (size_t i = 0; i < dict->hashmap_size; ++i) {
        
        aiv_dict_node_t* node = dict->hashmap[i];
        //Select all nodes of every bucket
        while (node) {
            aiv_dict_node_t* next = node->next;
            free(node->key);
            free(node);
            node = next;//node is the next element of the list
        }
    }
    free(dict->hashmap);
    dict->hashmap = NULL;
    dict->items_count = 0;
}

/* Debug print for key/int value */
void aiv_dict_debug_print_ints(aiv_dict_t* dict) {
    for (size_t i = 0; i < dict->hashmap_size; ++i) {
        printf("[%llu]", i);
        aiv_dict_node_t* node = dict->hashmap[i];
        while (node) {
            int k = 0, v = 0;
            //for now this print work only for int keys (and int values),
            if (node->key_size >= sizeof(int)) {//here i used the key_size field to avoid strange prints if key different from int
                k = *(int*)node->key;
            }
            v = *(int*)node->value;
            printf(" --> (k:%d,v:%d)", k, v);
            node = node->next;
        }
        printf("\n");
    }
}