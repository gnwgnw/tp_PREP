#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>

typedef struct Matrix {
    int col;
    int row;
    double* data;
} Matrix;


int assert(int assertion, char* message);
Matrix* multiply(Matrix* matrix_1, Matrix* matrix_2);
Matrix* create_matrix_from_file(FILE* file);
Matrix* create_matrix(int row, int col);
void free_matrix(Matrix* matrix);
double get_elem(Matrix* matrix, int row, int col);
void set_elem(Matrix* matrix, int row, int col, double val);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);
void display(Matrix* matrix);
void copy_matrix(Matrix* matrix1, Matrix* matrix2);

#endif //_MATRIX_H_
