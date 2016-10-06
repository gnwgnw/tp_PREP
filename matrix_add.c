#include<stdio.h>
#include<stdlib.h>
#include"matrix_add.h"

Matrix* resize_matrix(Matrix* mtrx, int nrow, int ncol)
{
    if(mtrx == NULL)
        return NULL;

    if(nrow <= 0 || ncol <= 0)
    {
        free_matrix(mtrx);
        return NULL;
    }

    Matrix *n_mtrx = create_matrix(nrow, ncol);
    nrow = nrow < get_rows(mtrx) ? nrow : get_rows(mtrx);
    ncol = ncol < get_cols(mtrx) ? ncol : get_cols(mtrx);
    for(int i = 0; i < nrow; i++)
        for(int j = 0; j < ncol; j++)
            set_elem(n_mtrx, i, j, get_elem(mtrx, i, j));//n_mtrx->ptr[i][j] = mtrx->ptr[i][j];
    /*int size = nrow*ncol;
    size = size < mtrx->row*mtrx->col ? size : mtrx->row*mtrx->col;
    memcpy(n_mtrx, mtrx, size);*/

    free_matrix(mtrx);

    n_mtrx->col = ncol;
    n_mtrx->row = nrow;

    return n_mtrx;
}

void print_matrix(FILE *f, Matrix* mtrx)
{
    if(f == NULL)
        return;
    if(mtrx == NULL)
        return;

    int rows = get_rows(mtrx);
    int cols = get_cols(mtrx);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            printf(" %4.3lf ", get_elem(mtrx, i, j));
        printf("\n");
    }
}

Matrix* mult_matrix(Matrix *mtrx1, Matrix *mtrx2, int *errcode)
{
    if(mtrx1 == NULL || mtrx2 == NULL)
    {
        *errcode = -1;
        return NULL;
    }

    if(get_cols(mtrx1) != get_rows(mtrx2))
    {
        *errcode = -2;
        return NULL;
    }

    int rows = get_rows(mtrx1);
    int cols = get_cols(mtrx2);
    int cols_1 = get_cols(mtrx1);

    Matrix *res = create_matrix(rows, cols);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
        {
            double sum = 0;
            for(int k = 0; k < cols_1; k++)
                sum += get_elem(mtrx1, i, k) * get_elem(mtrx2, k, j);
            set_elem(res, i, j, sum);
        }
    return res;
}
