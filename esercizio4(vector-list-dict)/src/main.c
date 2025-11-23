#include "aiv_vector.h"
#include "aiv_list.h"
#include "aiv_dict.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int compare_int(void* item1, void* item2) {
    int v1 = *(int*)item1;
    int v2 = *(int*)item2;

    if (v1 < v2) return -1;
    else if (v1 == v2) return 0;
    else return 1;
}

void vector_example(){

    // aiv_vector_t vector;
    // aiv_vector_init(&vector);
    aiv_vector_t vector = aiv_vector_new();

    int i10 = 10;
    aiv_vector_add(&vector, &i10);

    void* item0 = vector.items[0];
    int* item0_int_ptr = (int*)item0;
    int item0_value = *item0_int_ptr;

    int value = *(int*)vector.items[0];
    printf("Value 0: %d\n", item0_value);
    printf("Value 0: %d\n", value);

    int i20 = 20;
    aiv_vector_add(&vector, &i20);
    printf("Value 1: %d\n", *(int*)vector.items[1]);

    printf("Value 2: %s\n", aiv_vector_at(&vector, 2) == NULL ? "true" : "false");

    aiv_vector_destroy(&vector);

    int array[5] = {3, 5, 2, 1, 4};
    aiv_vector_t vector2 = aiv_vector_new();

    aiv_vector_add(&vector2, &array[0]);
    aiv_vector_add(&vector2, &array[1]);
    aiv_vector_add(&vector2, &array[2]);
    aiv_vector_add(&vector2, &array[3]);
    aiv_vector_add(&vector2, &array[4]);

    for (int i = 0; i < 5; ++i) {
        printf("vector2[%d] = %d\n", i, *(int*)aiv_vector_at(&vector2, i));
    }
     puts("=== NOW order ===");
    aiv_vector_sort_bubble(&vector2,compare_int);

    for (int i = 0; i < 5; ++i) {
        printf("vector2[%d] = %d\n", i, *(int*)aiv_vector_at(&vector2, i));
    }

    aiv_vector_set(&vector2, 0, &array[0]);
    aiv_vector_set(&vector2, 1, &array[1]);
    aiv_vector_set(&vector2, 2, &array[2]);
    aiv_vector_set(&vector2, 3, &array[3]);
    aiv_vector_set(&vector2, 4, &array[4]);
        
    puts("=== BUBBLE SORT 2 ===");
    aiv_vector_print_int(&vector2);
    puts("=== NOW order ===");
    aiv_vector_sort_bubble2(&vector2,compare_int);
    aiv_vector_print_int(&vector2);

    aiv_vector_set(&vector2, 0, &array[0]);
    aiv_vector_set(&vector2, 1, &array[1]);
    aiv_vector_set(&vector2, 2, &array[2]);
    aiv_vector_set(&vector2, 3, &array[3]);
    aiv_vector_set(&vector2, 4, &array[4]);
        
    puts("=== BUBBLE SORT 3 FROM SLIDE ===");
    aiv_vector_print_int(&vector2);
    puts("=== NOW order ===");
    my_aiv_vector_sort_bubble(&vector2,compare_int);
    aiv_vector_print_int(&vector2);

    
    aiv_vector_set(&vector2, 0, &array[0]);
    aiv_vector_set(&vector2, 1, &array[1]);
    aiv_vector_set(&vector2, 2, &array[2]);
    aiv_vector_set(&vector2, 3, &array[3]);
    aiv_vector_set(&vector2, 4, &array[4]);
        
    puts("=== QUICK SORT 3 FROM SLIDE ===");
    aiv_vector_print_int(&vector2);
    puts("=== NOW order ===");
    my_aiv_vector_sort_bubble(&vector2,compare_int);
    aiv_vector_print_int(&vector2);

     puts("=== Memomory Deletion (index 4 and 3) ===");

    //Deletion ad memory free
    aiv_vector_delete(&vector2,4);
    aiv_vector_delete(&vector2,3);

    aiv_vector_print_int(&vector2);

    aiv_vector_delete(&vector2,2);
    aiv_vector_delete(&vector2,1);
    aiv_vector_delete(&vector2,0);





}

void list_examples() {
    aiv_list_t list = aiv_list_new();

    int i10 = 10;
    aiv_list_add(&list, &i10);

    int i20 = 20;
    aiv_list_add(&list, &i20);

    int i30 = 30;
    aiv_list_add(&list, &i30);

    printf("Head: %d\n", *(int*)list.head->data);
    printf("Tail: %d\n", *(int*)list.tail->data);



    printf("Initial list size: %llu\n", aiv_list_get_size(&list));

    aiv_list_print(&list);

        // Modifying the second element (index 1)
    int new_value = 99;
    if (aiv_list_set_item_at(&list, 1, &new_value)) {
        printf("\nUpdated item at index 1!\n");
    }

    printf("\nList after modification:\n");
    for (size_t i = 0; i < aiv_list_get_size(&list); i++) {
        int* value = (int*)aiv_list_get_item_at(&list, i);
        printf("Item at index %llu: %d\n", i, *value);
    }

    // Removing the element in position index 1
    aiv_list_remove_item_at(&list, 1);
    printf("List size after remove_at(1): %zu\n", aiv_list_get_size(&list));

    for (size_t i = 0; i < aiv_list_get_size(&list); i++) {
        int* value = (int*)aiv_list_get_item_at(&list, i);
        printf("Item at index %llu: %d\n", i, *value);
    }

    // removing an element searched by value (30)
    aiv_list_remove_item(&list, &i30);
    printf("List size after remove_item(&i30): %zu\n", aiv_list_get_size(&list));

    for (size_t i = 0; i < aiv_list_get_size(&list); i++) {
        int* value = (int*)aiv_list_get_item_at(&list, i);
        printf("Item at index %llu: %d\n", i, *value);
    }

    // Free all memory
    aiv_list_destroy(&list);

}


size_t dummy_hash(void *key, size_t keylen) {
    return 0;
}

// Bernstein classic hash also here
size_t djb33x_hash(void *key, size_t keylen) {
    register int hash = 5381;
    int i;

    unsigned char *key_as_num = (unsigned char *)key;

    for (i = 0; i < keylen; i++) {
        hash = ((hash << 5) + hash) ^ key_as_num[i];
    }

    return hash;
}

void dict_examples() {

    /* LESSON EXAMPLE
    aiv_dict_t dict = aiv_dict_new();

    int key1 = 1;
    int val1 = 10;

    aiv_dict_put(&dict, &key1, sizeof(int), &val1);

    // key1 = 5;
    // int key1_original = 1;
    // void* val1_ptr = aiv_dict_get(&dict, &key1_original);
    // aiv_dict_put(&dict, &key1, sizeof(int), &val1);

    aiv_dict_t dict2 = aiv_dict_new_with_params(1, dummy_hash);
*/

    //MY NEW EXAMPLE FROM ZERO
    aiv_dict_t dict = aiv_dict_new_with_params(8, djb33x_hash); // 8 array elements, and hash fun

    int k1=4,v1=2, k2=8,v2=6, k3=5,v3=1, k4=6,v4=8, k5=7,v5=6, k6=14,v6=11, k7=21,v7=3;

    aiv_dict_put(&dict, &k1, sizeof(int), &v1);
    aiv_dict_put(&dict, &k2, sizeof(int), &v2);
    aiv_dict_put(&dict, &k3, sizeof(int), &v3);
    aiv_dict_put(&dict, &k4, sizeof(int), &v4);
    aiv_dict_put(&dict, &k5, sizeof(int), &v5);
    aiv_dict_put(&dict, &k6, sizeof(int), &v6);
    aiv_dict_put(&dict, &k7, sizeof(int), &v7);
    
    printf("Hasmap Size: %llu\n", aiv_dict_get_hashmap_elements_size(&dict));
    printf("Element Size: %llu\n", aiv_dict_get_size(&dict));
    aiv_dict_debug_print_ints(&dict);

    // GET 
    int q = 14;
    int* pv = (int*)aiv_dict_get(&dict, &q, sizeof(int));
    if (pv) printf("Get(%d) = %d\n", q, *pv);

    // CONTAINS 
    printf("Contains %d? %s\n", q, aiv_dict_contains_key(&dict, &q, sizeof(int)) ? "yes" : "no");

    // REMOVE 
    int r = 7;
    if (aiv_dict_remove(&dict, &r, sizeof(int))) {
        printf("Removed key %d\n", r);
    }

    printf("After remove:\n");
    printf("Size: %llu\n", aiv_dict_get_size(&dict));
    aiv_dict_debug_print_ints(&dict);
    

    aiv_dict_destroy(&dict);

  

}



int main() {
   
    puts("===================");
    puts("=== VECTOR PART ===");
    puts("===================");
    vector_example();
    puts("===================");
    puts("==== LIST PART ====");
    puts("===================");
    list_examples();
    puts("===================");
    puts("==== DICT PART ====");
    puts("===================");
    dict_examples();
    puts("===================");
    puts("======= BYE =======");
    puts("===================");
    return 0;
}