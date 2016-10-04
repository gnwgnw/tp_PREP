#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>

typedef struct Matrix {
    int size_rows;
    int size_cols;
    int len_matrix;
    int ind_row;
    int ind_col;
    double value;
    int type_create_matrix; //0-file, 1 -ручками через Matrix* create_matrix(int row, int col);
} Matrix;

Matrix* create_matrix_from_file(FILE* file);    //complete
Matrix* create_matrix(int row, int col);        //complete
void free_matrix(Matrix* matrix);               //complete
double get_elem(Matrix* matrix, int row, int col);              //complete
void set_elem(Matrix* matrix, int row, int col, double val);    //complete
int get_rows(Matrix* matrix);   //complete
int get_cols(Matrix* matrix);

#endif //_MATRIX_H_
