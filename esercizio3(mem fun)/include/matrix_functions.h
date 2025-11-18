#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

#include <stddef.h>

struct matrix{
    int* data;
    int n_rows;
    int m_columns;
}typedef int_matrix;

struct matrix_array{
    int** data;
    int n_rows;
    int m_columns;
}typedef int_matrix_array;

/* create/destroy (destroy opzionali se li aggiungi altrove) */
int_matrix_array create_int_matrix_array(int n_rows,int m_columns);
int_matrix       create_int_matrix(int n_rows,int m_columns);

/* print */
void int_matrix_array_print(const int_matrix_array matrix_array);
void int_matrix_print(const int_matrix matrix);

/* getters/setters */
int* int_matrix_get_pointer(const int_matrix matrix,int raw_position,int col_postition);
int  int_matrix_get_value(const int_matrix matrix,int raw_position,int col_postition);
int  int_matrix_get_size(const int_matrix matrix);
void initiate_int_matrix(int_matrix matrix,int value);
void int_matrix_set(int_matrix matrix,int raw_position,int col_postition,int new_value);
void destroy_int_matrix_array(int_matrix_array m);

#endif /* MATRIX_FUNCTIONS_H */
