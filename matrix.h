#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>

typedef struct Matrix {
    double** arr;
    int rows; //строки
    int cols; // столбцы
} Matrix;

Matrix* create_matrix_from_file(FILE* file);
Matrix* create_matrix(const int row,const int col);
void free_matrix(Matrix* matrix);
double get_elem(Matrix* matrix,const int row,const int col);
void set_elem(Matrix* matrix,const int row,const int col,const double val);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);

#endif //_MATRIX_H_
