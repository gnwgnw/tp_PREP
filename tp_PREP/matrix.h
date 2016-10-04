//
// Created by Pasha on 02.10.2016.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <stdio.h>

typedef struct Matrix {
    double **matrix;
    int number_of_row;
    int number_of_col;
} Matrix;

Matrix* create_matrix_from_file(FILE* file);
Matrix* create_matrix(int row, int col);
void free_matrix(Matrix* matrix);
double get_elem(Matrix* matrix, int row, int col);
void set_elem(Matrix* matrix, int row, int col, double val);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);

#endif //MATRIX_MATRIX_H
