#ifndef AIV_UNIT_H
#define AIV_UNIT_H

#include <stdio.h>
#include <stddef.h>

#define AIV_UNIT_INT_EQ(expected, actual) \
    if ((expected) != (actual)) { \
        printf("%s: expected %d but was %d [%s@%d]\n", \
               __FUNCTION__, expected, actual, __FILE__, __LINE__); \
    }

#define AIV_UNIT_IS_TRUE(actual) \
    if ((actual) == 0) { \
        printf("%s: expected %s but was %s [%s@%d]\n", \
               __FUNCTION__, "true", "false", __FILE__, __LINE__); \
    }

#define AIV_UNIT_TEST(name) void name()
    
#define AIV_UNIT_RUNNER(...) \
    int main() { \
        void (*tests[])() = { __VA_ARGS__ }; \
        size_t tests_size = sizeof(tests); \
        size_t ptr_size = sizeof(tests[0]); \
        size_t test_count = tests_size / ptr_size; \
        for (size_t i = 0; i < test_count; ++i) { \
            tests[i](); \
        } \
        printf("All tests executed: %zu\n", test_count); \
        return 0; \
    }

//my adds

#define AIV_UNIT_IS_NULL(ptr) \
    if ((ptr) != NULL) { \
        printf("%s: expected NULL but was %p [%s@%d]\n", \
               __FUNCTION__, (void*)(ptr), __FILE__, __LINE__); \
    }
//pointer void* compare
#define AIV_UNIT_PTR_EQ(expected, actual) \
    if ((expected) != (actual)) { \
        printf("%s: expected pointer %p but was %p [%s@%d]\n", \
               __FUNCTION__, (void*)(expected), (void*)(actual), __FILE__, __LINE__); \
    }
//size compare
#define AIV_UNIT_SIZE_EQ(expected, actual) \
    if ((expected) != (actual)) { \
        printf("%s: expected size %zu but was %zu [%s@%d]\n", \
               __FUNCTION__, (size_t)(expected), (size_t)(actual), __FILE__, __LINE__); \
    }



#endif // AIV_UNIT_H

//1:45
//1:17