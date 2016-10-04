#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Matrix {
	uint32_t rows;
	uint32_t cols;
    uint32_t row;
    uint32_t col;
    double val;
} Matrix;

Matrix* create_matrix_from_file(FILE* file);
Matrix* create_matrix(int row, int col);
void free_matrix(Matrix* matrix);
double get_elem(Matrix* matrix, int row, int col);
void set_elem(Matrix* matrix, int row, int col, double val);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);

#endif //_MATRIX_H_
