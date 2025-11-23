#include "aiv_list.h"
#include <stdlib.h>
#include <stdio.h>

aiv_list_t aiv_list_new() {
    aiv_list_t list;
    list.head = NULL;
    list.tail = NULL;
    list.count = 0;
    return list;
}

void aiv_list_destroy(aiv_list_t* list) {
    aiv_list_node_t* current = list->head;
    while (current) {
        aiv_list_node_t* next = current->next;
        free(current);
        current = next;
    }
}

bool aiv_list_is_empty(aiv_list_t* list) {
    return list->count == 0;
}

void aiv_list_add(aiv_list_t* list, void* item) {
    aiv_list_node_t* node = (aiv_list_node_t*)malloc(sizeof(aiv_list_node_t));
    node->data = item;
    node->prev = NULL;
    node->next = NULL;

    if (aiv_list_is_empty(list)) {
        list->head = node;
        list->tail = node;
    } else { // node1 <-- node2
        aiv_list_node_t* prev = list->tail;
        node->prev = prev;
        prev->next = node;
        list->tail = node;
    }

    list->count++;
}

//GET and SET functions 

size_t aiv_list_get_size(aiv_list_t* list) {
    return list->count;
}

void* aiv_list_get_item_at(aiv_list_t* list, size_t index) {
    if (index >= list->count) {
        return NULL; // index out of bound
    }

    aiv_list_node_t* current = list->head;
    size_t i = 0;

    while (current && i < index) {
        current = current->next;
        i++;
    }

    return current ? current->data : NULL; //it shouldnt be  necessary but implemented here a null safe controll
}

bool aiv_list_set_item_at(aiv_list_t* list, size_t index, void* item) {
    if (index >= list->count) {
        return false; // index out of bound
    }
    //same search as get
    aiv_list_node_t* current = list->head;
    size_t i = 0;

    while (current && i < index) {
        current = current->next;
        i++;
    }

    //if not null set the current element with new value
    if (current) {
        current->data = item;
        return true;
    }

    return false;
}

//NOW remove functions:

bool aiv_list_remove_item(aiv_list_t* list, void* item) {
    aiv_list_node_t* current = list->head;

    //this while have not counter cause we have to search the value throught all elements until we found it
    while (current) {
        if (current->data == item) {
            // if value is in the first node
            if (current == list->head) {
                list->head = current->next;
                if (list->head) list->head->prev = NULL;//null safe check
            }
            // if value is in last node
            else if (current == list->tail) {
                list->tail = current->prev;
                if (list->tail) list->tail->next = NULL;//null safe check also here
            }
            // value in a middle node
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            //free memory part and update list size
            free(current);
            list->count--;
            return true; //break func if node found
        }
        //search from head to tail
        current = current->next;
    }

    return false; // value not found
}

bool aiv_list_remove_item_at(aiv_list_t* list, size_t index) {
    if (index >= list->count) return false;

    aiv_list_node_t* current = list->head;
    size_t i = 0;

    //Searcing part same as get function
    while (current && i < index) {
        current = current->next;
        i++;
    }
    //Same security null check
    if (!current) return false;

    // Remove part same as remove_item function
    if (current == list->head) {
        list->head = current->next;
        if (list->head) list->head->prev = NULL;
    } else if (current == list->tail) {
        list->tail = current->prev;
        if (list->tail) list->tail->next = NULL;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    
    free(current);
    list->count--;

    return true;
}

//print fun
void aiv_list_print(aiv_list_t* list) {

    for (size_t i = 0; i < aiv_list_get_size(list); i++) {
            int* value = (int*)aiv_list_get_item_at(list, i);
            printf("Item at index %llu: %d\n", i, *value);
        }
}