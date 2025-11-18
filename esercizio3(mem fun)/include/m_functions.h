#include <stddef.h>
void* my_memset(void *_Dst, int _Val, size_t _Size);
void* my_calloc(int n, size_t _Size);
void* my_memcpy(void *_Dst, const void *_Src, size_t _Size);
//void* my_original_realloc(void *_Block, size_t _Size);
void* my_realloc(void *ptr, size_t new_size, size_t old_size);


