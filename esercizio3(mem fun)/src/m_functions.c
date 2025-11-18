#include <stddef.h>
#include <stdlib.h>
void* my_memset(void *_Dst, int _Val, size_t _Size){
    //it look like standard function use unsisgned char cause on values over 127 in fuctions using byte comparision the value will be interpreted as negative,and there is the risk to change the real byte for byte value meaning
    unsigned char *ptr = (unsigned char *)_Dst; // accede ai byte
    unsigned char byte_val = (unsigned char)_Val; // prende solo il byte meno significativo

    //This time we have a dimension so i decide to use a for
    for (size_t i = 0; i < _Size; i++) {
        ptr[i] = byte_val;
    }

    return _Dst;// original destination pointer
}

void* my_calloc(int n, size_t _Size){
    if (_Size == 0) {
        // if size is = null then  return null
        return NULL;
    }
    void *ptr= malloc(n*_Size);
    my_memset(ptr, 0,n*_Size);
    return ptr;
}

void* my_memcpy(void *_Dst, const void *_Src, size_t _Size) {
    //it look like standard function use unsisgned char cause on values over 127 in fuctions using byte comparision the value will be interpreted as negative,and there is the risk to change the real byte for byte value meaning
    const unsigned char *source = (const unsigned char *)_Src;
    unsigned char       *dest = (unsigned char *)_Dst;
   
    //This time we have a dimension so i decide to use a for
    for (size_t i = 0; i < _Size; i++) {
        dest[i] = source[i];
    }
    return _Dst; // original destination pointer
}

//seems that (according with the documentation that i found)the original realloc use a particular system run time allocation to know the old allocation size for that referement
//void* my_original_realloc(void *_Block, size_t _Size){
//}

void* my_realloc(void *ptr, size_t new_size, size_t old_size) {
    if (ptr == NULL) {
        // if ptr = NULL :same of malloc
        return malloc(new_size);
    }
    if (new_size == 0) {
        // if size of prt !=null but new size is = null then here we free the actual memory and return null
        free(ptr);
        return NULL;
    }

    // new memory area
    void *new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;  // fail

    //copy the old buffer values on the new one (i assumed that the new buffer is longer than the old one)
    //UPDATE:now if new size is shorter it copy only the first "new_size" values of the old buffer
    size_t to_copy_size = (old_size < new_size) ? old_size : new_size;
    my_memcpy(new_ptr, ptr, to_copy_size);

    // free old dynamic memory allocation
    free(ptr);
    //return the new one
    return new_ptr;
}
