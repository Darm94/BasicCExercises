#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_functions.h"

//INT MATRIX WITH POINTER ARRAYS
int_matrix_array create_int_matrix_array(int n_rows,int m_columns){//to study
    int_matrix_array matrix;
    matrix.n_rows   = n_rows;
    matrix.m_columns= m_columns;
    matrix.data     = NULL;

    matrix.data = (int **)malloc((size_t)n_rows * sizeof *matrix.data);
    if (!matrix.data) {
        matrix.n_rows = matrix.m_columns = 0;
        return matrix;
    }

    for (int r = 0; r < n_rows; r++) {
        matrix.data[r] = (int *)malloc((size_t)m_columns * sizeof *matrix.data[r]);
        if (!matrix.data[r]) {
            for (int i = 0; i < r; i++) free(matrix.data[i]);
            free(matrix.data);
            matrix.data = NULL;
            matrix.n_rows = matrix.m_columns = 0;
            return matrix;
        }
        //initialization to 0 for every element
        for (int c = 0; c < m_columns; c++) matrix.data[r][c] = 0;
    }

    return matrix;
}

void int_matrix_array_print(const int_matrix_array matrix_array){
    for(int i = 0 ; i<matrix_array.n_rows ; i++){
        for(int j=0 ; j< matrix_array.m_columns; j++){
            printf("[%d] ", matrix_array.data[i][j]);
        }
        puts("");
    }
}

//INT MATRIX WITH UNIQUE POINTER
int_matrix create_int_matrix(int n_rows,int m_columns){
    int_matrix matrix;
    matrix.data = (int*)malloc(sizeof(int) * n_rows * m_columns);
    matrix.n_rows=n_rows;
    matrix.m_columns=m_columns;
    return matrix;
}

int* int_matrix_get_pointer(const int_matrix matrix,int raw_position,int col_postition){
    int new_index = (raw_position * matrix.m_columns)+col_postition;
    return matrix.data+new_index;
}

int int_matrix_get_value(const int_matrix matrix,int raw_position,int col_postition){
    int new_index = (raw_position * matrix.m_columns)+col_postition;
    return *(matrix.data+new_index);
}

int int_matrix_get_size(const int_matrix matrix){
    return matrix.m_columns * matrix.n_rows;
}

void initiate_int_matrix(int_matrix matrix,int value){
    int* index = matrix.data;
    int size= int_matrix_get_size(matrix);
    for(int i=0; i<size ; i++){
        *index=value;
        index++;
    }
}

void int_matrix_set(int_matrix matrix,int raw_position,int col_postition,int new_value){
    int new_index = (raw_position * matrix.m_columns)+col_postition;
    *(matrix.data+new_index)=new_value;
    *(matrix.data+new_index)=new_value; // (nota: riga duplicata, ma lasciata uguale come richiesto)
    return ;
}

void int_matrix_print(const int_matrix matrix){
    int matrix_size = int_matrix_get_size(matrix);
    for(int i=0 ; i<matrix_size ; i++){
        printf("%s[%d]", i%matrix.m_columns ? "" : "\n", matrix.data[i]);
    }
    printf("\n");
}
