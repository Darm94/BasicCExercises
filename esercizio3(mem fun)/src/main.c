#include "s_functions.h"
#include "m_functions.h"
#include "matrix_functions.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>



int main (int argc, char** argv)
{
    size_t size = 2;
    void* mem_ptr = malloc(size);
    if (mem_ptr == 0) {         // if (!mem_ptr)
        puts("failed!");
        return -1;
    }

    if (mem_ptr == NULL)
        return -1;

    if (mem_ptr)
        printf("mem addr: %p\n", mem_ptr);

int num_size = 3 * sizeof(int);
int* numbers = (int*)malloc(num_size);
numbers[0] = 1;







printf("================    MALLOC dyn. array of size 3:   ================\n");
for (int i = 0; i < 3; i++)
    printf("num[%d] = %d\n", i, numbers[i]);

printf("================    MEMSET function on array but setting 100 for every byte (the numbers become a very big number instead 100)   ================\n");
// attention to using values greater than 0 (for non-char type)
memset(numbers, 100, num_size);
for (int i = 0; i < 3; i++)
    printf("num[%d] = %d\n", i, numbers[i]);

free(numbers);

printf("================    CALLOC dyn. array of size 3 (setting all values to 0):   ================\n");
// malloc + memset
numbers = (int*)calloc(3, sizeof(int));
for (int i = 0; i < 3; i++)
    printf("num[%d] = %d\n", i, numbers[i]);

printf("================    REALLOC from dyn. array of size 3 to dyn. array of size 10(setting all values to 0):   ================\n");
// Worst case: malloc + memcpy + free
numbers = realloc(numbers, 10 * sizeof(int));
for (int i = 0; i < 10; i++)
    printf("num[%d] = %d\n", i, numbers[i]);
free(numbers);







printf("************************  NOW MY FUNCTIONS   ************************\n");

numbers = (int*)malloc(num_size);
numbers[0] = 1;
printf("================    MALLOC dyn. array of size 3:   ================\n");
for (int i = 0; i < 3; i++)
    printf("num[%d] = %d\n", i, numbers[i]);

printf("================    MY_MEMSET function on array but setting 100 for every byte (the numbers become a very big number instead 100)   ================\n");
// attention to using values greater than 0 (for non-char type)
my_memset(numbers, 100, num_size);
for (int i = 0; i < 3; i++)
    printf("num[%d] = %d\n", i, numbers[i]);

free(numbers);

printf("================    MY_CALLOC dyn. array of size 3 (setting all values to 0):   ================\n");
// malloc + memset
numbers = (int*)my_calloc(3, sizeof(int));
for (int i = 0; i < 3; i++)
    printf("num[%d] = %d\n", i, numbers[i]);

printf("================    MY_REALLOC from dyn. array of size 3 to dyn. array of size 10(setting all values to 0):   ================\n");
// Worst case: malloc + memcpy + free
numbers = my_realloc(numbers, 10 * sizeof(int),num_size);
for (int i = 0; i < 10; i++)
    printf("num[%d] = %d\n", i, numbers[i]);
free(numbers);







printf("************************  Now dynamic matrix using struct and functions   ************************\n");

int_matrix matrix = create_int_matrix(5,4);
initiate_int_matrix(matrix,1);

printf("ALL Matrix Elements values");
int_matrix_print(matrix);

printf("\nALL Matrix Elements values after set on matrix[0][3]=2 and matrix[1][2]=9 ");
int_matrix_set(matrix,0,3,2);
int_matrix_set(matrix,1,2,9);
int_matrix_print(matrix);

printf("\nALL Matrix Elements values after get_pointer and then set doing: matrix[2][0]=5");
*(int_matrix_get_pointer(matrix,2,0))=5;
int_matrix_print(matrix);

printf("\nValue at Matrix[%d][%d] = %d",1,2,int_matrix_get_value(matrix,1,2));








printf("\n************************  Now dynamic matrix using pointer strategy,struct and functions   ************************\n");
int_matrix_array matrix_array = create_int_matrix_array(5,4);//i decided to initialize directly all elements to 0 here in the creation function

printf("ALL Matrix Elements values\n");
int_matrix_array_print(matrix_array);

printf("\nALL Matrix Elements values after set on matrix[0][3]=2 and matrix[1][2]=9\n");
matrix_array.data[0][3]=2;
matrix_array.data[1][2]=9;
int_matrix_array_print(matrix_array);

printf("\nALL Matrix Elements values after get_pointer and then set doing: matrix[2][1]=5\n");
*(matrix_array.data[2]+1)=5;
int_matrix_array_print(matrix_array);

printf("\nValue at Matrix[%d][%d] = %d",1,2,matrix_array.data[1][2]);

//lets free the memory
free(matrix.data);
destroy_int_matrix_array(matrix_array);

printf("\n************************  BYE TO THE NEXT EXERCISEE   ************************\n");




}