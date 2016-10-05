#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
    int row_ind;
    int col_ind;
    double elem;
} Element;

typedef struct Matrix {
    int row;
    int col;
    Element* elems;
} Matrix;


Matrix* create_matrix_from_file(FILE* file);
Matrix* create_matrix(int row, int col);
void free_matrix(Matrix* matrix);
double get_elem(Matrix* matrix, int row, int col);
void set_elem(Matrix* matrix, int row, int col, double val);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);


#endif // MATRIX_H
