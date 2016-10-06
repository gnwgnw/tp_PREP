#ifndef MATRIX_ADD_H
#define MATRIX_ADD_H

#include"Matrix.h"

#define WrongArgs -1;
#define  ErrExit -2;

Matrix* resize_matrix(Matrix* mtrx, int nrow, int ncol);
void print_matrix(FILE *f, Matrix* mtrx);
Matrix* mult_matrix(Matrix *mtrx1, Matrix *mtrx2, int *errcode);

#endif // MATRIX_ADD_H
