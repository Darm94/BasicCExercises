#include "aiv_vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

aiv_vector_t aiv_vector_new() {
    aiv_vector_t vector;
    vector.items = NULL;
    vector.count = 0;
    vector.capacity = 10;
    return vector;
}

void aiv_vector_destroy(aiv_vector_t* vector) {
    if (!vector->items) return;

    free(vector->items);
    vector->items = NULL;
    vector->count = 0;
    vector->capacity = 0;
}

void aiv_vector_add(aiv_vector_t* vector, void* item) {
    size_t new_index = vector->count;
    vector->count++;
    vector->items = realloc(vector->items, sizeof(void*) * vector->count);
    vector->items[new_index] = item;
}

void* aiv_vector_at(aiv_vector_t* vector, size_t index) {
    if (index >= vector->count) {
        return NULL;
    }
    return vector->items[index];
}

void aiv_vector_sort_bubble(aiv_vector_t *vector,
                            int (*comparator)(void *, void *)) {
    for (size_t i = 0; i < vector->count; i++) {
        for (size_t j = 0; j < vector->count; j++) {
            int comp = comparator(vector->items[i], vector->items[j]);
            if (comp < 0) {
                void *tmp = vector->items[i];
                vector->items[i] = vector->items[j];
                vector->items[j] = tmp;
            }
        }
    }
}
//here the my bubble version ispired by pseudo-code showed at lesson
void aiv_vector_sort_bubble2(aiv_vector_t *vector,
                            int (*comparator)(void *, void *)) {
    if (vector == NULL || vector->count < 2) return;

    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (size_t i = 0; i < vector->count - 1; i++) {
            if (comparator(vector->items[i], vector->items[i + 1]) > 0) {
                void *tmp = vector->items[i];
                vector->items[i] = vector->items[i + 1];
                vector->items[i + 1] = tmp;
                swapped = 1;
            }
        }
    }
}

//here the my bubble version ispired  lesson part and forums on web
void my_aiv_vector_sort_bubble(aiv_vector_t *vector,
                            int (*comparator)(void *, void *)) {
    if (vector == NULL || vector->count < 2) return;

    while(1) {
        int swapped = 0;
        for (size_t i = 0; i < vector->count - 1; i++) {
            if (comparator(vector->items[i], vector->items[i + 1]) > 0) {
                void *tmp = vector->items[i];
                vector->items[i] = vector->items[i + 1];
                vector->items[i + 1] = tmp;
                swapped = 1;
            }
        }

        // no element swapped = array sorted
        if (!swapped) {
            break;
        }
    }
}

static void quicksort_internal(void **items, int left, int right, int (*cmp)(void *, void *)) {
    int i = left;
    int j = right;
    void *pivot = items[(left + right) / 2]; // pivot at center way

    while (i <= j) {
        //this two while are sequetial and they cant be togheter longer than O(N)
        while (cmp(items[i], pivot) < 0) i++; //here i directly increment i until the first alement to swap
        while (cmp(items[j], pivot) > 0) j--; //same thing with j
       
        if (i <= j) {
            //swap part
            void *tmp = items[i];
            items[i] = items[j];
            items[j] = tmp;
            i++;
            j--;
        }
        //after the last swap i and j increment so in i>j they can be used for the recursive call of quicksort_internal
        //if is still <=j ,but items[i] is greater than pivot i will not be incrementet ad the beggining of the
        //cicle and will be swapped with the next j minor than pivot
    }

    if (left < j) quicksort_internal(items, left, j, cmp);//left part
    if (i < right) quicksort_internal(items, i, right, cmp);//right part
}

void aiv_vector_sort_quick(aiv_vector_t *vector, int (*comparator)(void *, void *)) {
    if (vector == NULL || vector->count < 2) return;
    quicksort_internal(vector->items, 0, (int)vector->count - 1, comparator);
}

void aiv_vector_set(aiv_vector_t *vector, size_t index, void *item) {
    if (index >= vector->count) {
        // out of vector range -> Nothing to do
        return;
    }

    vector->items[index] = item;
}

void aiv_vector_delete(aiv_vector_t *vector, size_t index) {
    if (vector == NULL || index >= vector->count) {
        return; // // out of vector range  or NULL -> Nothing to do
    }

    // shift to the left all element after index
    for (size_t i = index; i < vector->count - 1; i++) {
        vector->items[i] = vector->items[i + 1];
    }

    vector->count--;

    // realloc for reduce memory usage (if we want this logic)
    vector->items = realloc(vector->items, sizeof(void*) * vector->count);
}

void aiv_vector_print_int(aiv_vector_t *vector) {
    for (size_t i = 0; i < vector->count; ++i) {
        int *value = (int*)aiv_vector_at(vector, i);
        printf("vector[%llu] = %d\n", i, *value);
    }
}