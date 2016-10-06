#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct Matrix
{
    int cols;
    int rows;
    double value;
    int col;
    int row;
} Matrix;

Matrix* create_matrix_from_file(FILE* file);
Matrix* create_matrix(int row, int col);
void free_matrix(Matrix* matrix);
double get_elem(Matrix* matrix, int row, int col);
void set_elem(Matrix* matrix, int row, int col, double val);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);
double get_l_norm(Matrix *matrix, int row, int col);

#endif //_MATRIX_H_
