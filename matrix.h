#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>

typedef struct Matrix {
    double **matr;
    int rows;
    int cols;
} Matrix;

//Matrix *create_matrix_from_file(const char *filePath);
Matrix *create_matrix_from_file(FILE *file);
Matrix *create_matrix(int row, int col);
Matrix *add_row(Matrix *matrix);
Matrix *transpose(Matrix *matrix);
void free_matrix(Matrix *matrix);
void print_matrix(Matrix *matrix);
void set_elem(Matrix *matrix, int row, int col, double val);
int get_rows(Matrix *matrix);
int get_cols(Matrix *matrix);
double get_elem(Matrix *matrix, int row, int col);
double max_norm(Matrix *matrix);
double l_norm(Matrix *matrix);
double e_norm(Matrix *matrix);


#endif //_MATRIX_H_
