//file test_suite1.c
#define CLOVE_SUITE_NAME VectorSuite
#include "clove-unit.h"
#include "aiv_vector.h"

VECTOR_DEFINE(int)
VECTOR_DEFINE(float)
typedef int* int_ptr;
VECTOR_DEFINE(int_ptr)

CLOVE_TEST(CreateEmptyVector) {
    aiv_vector_t vector;
    aiv_vector_init(&vector,sizeof(char));
    CLOVE_SIZET_EQ(0, vector.count);
    CLOVE_NULL(vector.items);
    CLOVE_SIZET_EQ(1, vector.item_size);
}

CLOVE_TEST(AddOneItem) {
    aiv_vector_t vector;
    aiv_vector_init(&vector,sizeof(int));

    int i10=10;
    aiv_vector_add(&vector,&i10);//per ora passo puntatore ma potre voler passare il valore diretto

    CLOVE_SIZET_EQ(1, vector.count);
    CLOVE_INT_EQ(10,((int*)vector.items)[0]);

}

CLOVE_TEST(AddTwoItem) {
    aiv_vector_t vector;
    aiv_vector_init(&vector,sizeof(int));

    int i10=10;
    aiv_vector_add(&vector,&i10);

    int i20=20;
    aiv_vector_add(&vector,&i20);

    CLOVE_SIZET_EQ(2, vector.count);
    CLOVE_INT_EQ(10,((int*)vector.items)[0]);
    CLOVE_INT_EQ(20,((int*)vector.items)[1]);
}

CLOVE_TEST(GetFirstItem) {
    aiv_vector_t vector;
    aiv_vector_init(&vector,sizeof(int));

    int i10=10;
    aiv_vector_add(&vector,&i10);

    CLOVE_INT_EQ(10,*(int*)aiv_vector_get(&vector, 0));
}


//with vector define:

CLOVE_TEST(CreateEmptyVector2) {
    aiv_vector_t vector;
    // qui il test è sul vettore "grezzo" con char, lo lascio invariato:
    aiv_vector_init(&vector,sizeof(char));
    CLOVE_SIZET_EQ(0, vector.count);
    CLOVE_NULL(vector.items);
    CLOVE_SIZET_EQ(1, vector.item_size);
}

CLOVE_TEST(AddOneItem2) {
    aiv_vector_t vector;
    vector_int_init(&vector);          // <-- wrapper generato da VECTOR_DEFINE(int)

    vector_int_add(&vector, 10);       // invece di int i10 + aiv_vector_add(&vector,&i10);

    CLOVE_SIZET_EQ(1, vector.count);
    CLOVE_INT_EQ(10, vector_int_get(&vector, 0));
}

CLOVE_TEST(AddTwoItem2) {
    aiv_vector_t vector;
    vector_int_init(&vector);

    vector_int_add(&vector, 10);
    vector_int_add(&vector, 20);

    CLOVE_SIZET_EQ(2, vector.count);
    CLOVE_INT_EQ(10, vector_int_get(&vector, 0));
    CLOVE_INT_EQ(20, vector_int_get(&vector, 1));
}

CLOVE_TEST(GetFirstItem2) {
    aiv_vector_t vector;
    vector_int_init(&vector);

    vector_int_add(&vector, 10);

    CLOVE_INT_EQ(10, vector_int_get(&vector, 0));
}

//pointer test and prove it works
CLOVE_TEST(VectorOfIntPointers_Typed) {
    aiv_vector_t vector;
    vector_int_ptr_init(&vector);   // generato da VECTOR_DEFINE(int_ptr)

    int a = 10;
    int b = 20;

    int* pa = &a;
    int* pb = &b;

    vector_int_ptr_add(&vector, pa);
    vector_int_ptr_add(&vector, pb);

    CLOVE_SIZET_EQ(2, vector.count);

    int* v0 = vector_int_ptr_get(&vector, 0);
    int* v1 = vector_int_ptr_get(&vector, 1);

    CLOVE_INT_EQ(10, *v0);
    CLOVE_INT_EQ(20, *v1);

    aiv_vector_free(&vector);
}
