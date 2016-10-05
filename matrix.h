#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 332 // INT_MAX=10+INT_MAX=10+" "*2+double = 1+308;
typedef struct Matrix {
	int row;
	int col;
	double **matrix;
} Matrix;
// work functions
bool check_dimension(int dim); // checks matrix dimensions
bool check_index(int dim, int orig); // checks index for being out of bounds
void init_matrix(Matrix *m); // initializes matrix with zero values
int count_lexemes(char *str); // counts lexems in string
bool check_string(char *str, int checkcount); // validates the string
bool string_to_param(char *str, int *param); // get integer parameter from string
bool string_to_params(char *str, int *row, int *col, double *val); // get parameters from string

																   // target functions
Matrix* create_matrix_from_file(FILE* file);
Matrix* create_matrix(int row, int col);
void free_matrix(Matrix* matrix);
double get_elem(Matrix* matrix, int row, int col);
void set_elem(Matrix* matrix, int row, int col, double val);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);

#endif //_MATRIX_H_
