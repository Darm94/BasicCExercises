#include <stdio.h>
#include <stdlib.h>

#include "aiv_vector.h"
#include "aiv_list.h"
#include "aiv_dict.h"
#include "aiv-unit.h"


AIV_UNIT_TEST(test_list_new) {
    aiv_list_t list = aiv_list_new();
/*
    AIV_UNIT_IS_TRUE(list.head == NULL);   // implement AIV_UNIT_IS_NULL
    AIV_UNIT_IS_TRUE(list.tail == NULL);   // implement AIV_UNIT_IS_NULL
    //AIV_UNIT_INT_EQ(0, list.count);      
    AIV_UNIT_IS_TRUE(list.count == 0);     // implement AIV_UNIT_SIZE_EQ
*/

    AIV_UNIT_IS_NULL(list.head);
    AIV_UNIT_IS_NULL(list.tail);
    AIV_UNIT_SIZE_EQ(0, list.count);

}

AIV_UNIT_TEST(test_list_destroy) {
    // Initialization
    aiv_list_t list = aiv_list_new();

    int i1 = 1;
    aiv_list_add(&list, &i1);
    aiv_list_add(&list, &i1);
    aiv_list_add(&list, &i1);
    aiv_list_add(&list, &i1);

    // Execution
    aiv_list_destroy(&list);

    AIV_UNIT_IS_TRUE(list.count == 0);
    AIV_UNIT_IS_TRUE(list.head == NULL);
    AIV_UNIT_IS_TRUE(list.tail == NULL);
}

AIV_UNIT_TEST(test_list_add_one_item) {
    aiv_list_t list = aiv_list_new();

    int i1 = 1;
    aiv_list_add(&list, &i1);

    //AIV_UNIT_IS_TRUE(list.head == list.tail);     // implement AIV_UNIT_PTR_EQ
    AIV_UNIT_PTR_EQ(list.head, list.tail);
    AIV_UNIT_IS_TRUE(list.count == 1);
    AIV_UNIT_IS_TRUE(list.head->prev == NULL);
    AIV_UNIT_IS_TRUE(list.head->next == NULL);
    AIV_UNIT_IS_TRUE(list.head->data == &i1);
}

AIV_UNIT_TEST(test_list_add_two_items) {
    // Initialization
    aiv_list_t list = aiv_list_new();

    int i1 = 1;
    aiv_list_add(&list, &i1);

    // Execution
    int i2 = 2;
    aiv_list_add(&list, &i2);

    // Assertion
    // AIV_UNIT_IS_TRUE(list.head != list.tail); // TODO: Re-think..

    //tests modifiyed with new UNIT TESTS
    /*
    AIV_UNIT_IS_TRUE(list.head->data == &i1);
    AIV_UNIT_IS_TRUE(list.tail->data == &i2);
    AIV_UNIT_IS_TRUE(list.count == 2);
    AIV_UNIT_IS_TRUE(list.head->prev == NULL);
    AIV_UNIT_IS_TRUE(list.head->next == list.tail);
    AIV_UNIT_IS_TRUE(list.tail->prev == list.head);
    AIV_UNIT_IS_TRUE(list.tail->next == NULL);*/
    AIV_UNIT_PTR_EQ(&i1, list.head->data);
    AIV_UNIT_PTR_EQ(&i2, list.tail->data);
    AIV_UNIT_SIZE_EQ(2, list.count);
    AIV_UNIT_IS_NULL(list.head->prev);
    AIV_UNIT_PTR_EQ(list.tail, list.head->next);
    AIV_UNIT_PTR_EQ(list.head, list.tail->prev);
    AIV_UNIT_IS_NULL(list.tail->next);
}

AIV_UNIT_RUNNER(
    test_list_new,
    test_list_add_one_item,
    test_list_add_two_items,
    test_list_destroy
)