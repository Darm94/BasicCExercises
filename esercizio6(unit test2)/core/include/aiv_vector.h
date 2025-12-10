
#ifndef AIV_VECTOR_H
#define AIV_VECTOR_H

typedef struct aiv_vector {
    size_t count;
    void* items;
    size_t item_size;
}aiv_vector_t;

#define VECTOR_DEFINE(TYPE)                                                 \
    void vector_##TYPE##_init(aiv_vector_t* v) {                            \
        aiv_vector_init(v, sizeof(TYPE));                                   \
    }                                                                       \
                                                                            \
    void vector_##TYPE##_add(aiv_vector_t* v, TYPE value) {                 \
        aiv_vector_add(v, &value);                                          \
    }                                                                       \
                                                                            \
    TYPE vector_##TYPE##_get(aiv_vector_t* v, size_t index) {               \
        return *(TYPE*)aiv_vector_get(v, index);                            \
    }
    
void aiv_vector_init(aiv_vector_t* vector,size_t item_size);
void aiv_vector_free(aiv_vector_t* vector);
void aiv_vector_add(aiv_vector_t* vector,void* item);
void * aiv_vector_get(aiv_vector_t* vector, size_t index);
#endif //AIV_VECTOR_H
