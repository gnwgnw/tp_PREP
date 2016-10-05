#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 255
#define ERROR_EXIT 1
#define SUCCESS_EXIT 0

typedef struct {
	double** matrix;
	int rows_N;
	int cols_M;
} Matrix;

Matrix* create_matrix_from_file(FILE* file);
Matrix* create_matrix(int row, int col);
void free_matrix(Matrix* matrix);
double get_elem(Matrix* matrix, int row, int col);
void set_elem(Matrix* matrix, int row, int col, double val);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);
void check_file(FILE* file);
void print_matrix(Matrix* matrix);

#endif //_MATRIX_H_
