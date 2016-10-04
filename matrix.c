#include "matrix.h"

Matrix* create_matrix_from_file(FILE* file)
{
    int row = 0;
    int col = 0;

    fscanf(file, "%d", &row);
    fscanf(file, "%d", &col);

    Matrix *matr;
    matr = create_matrix(row, col);

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            fscanf(file, "%lf", &matr->cont[i][j]);
        }
    }
    return matr;
}

Matrix* create_matrix(int row, int col)
{
    int elem_num = row * col;
    struct Matrix* matr = malloc(sizeof(Matrix));

    matr->cont = malloc(sizeof(double*) * row);
    for (int i = 0; i < row; ++i)
    {
        matr->cont[i] = malloc(sizeof(double) * col);
    }

    matr->elem_num = row * col;
    matr->col_num = col;
    matr->row_num = row;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            matr->cont[i][j] = 0.0;
        }
    }

    return matr;
}

void show_matrix(Matrix *matr)
{
    int i = 0, j = 0;
    int row_num = matr->row_num;
    int col_num = matr->col_num;
    printf("\n");
    for (i = 0; i < row_num; i++) {
        for(j = 0; j < col_num; j++) {
            printf("%6.2f ", get_elem(matr, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(Matrix* matrix)
{
    for (int i = 0; i < matrix->row_num; ++i) {
        free(matrix->cont[i]);
    }
    free(matrix->cont);
    free(matrix);
    matrix = NULL;
}

double get_elem(Matrix* matrix, int row, int col)
{
    if (row >= matrix->row_num || col >= matrix->col_num) {
        printf("\nGetting element error:\nmatrix index out of range!\
            \nReturned 0\n");
        return 0.0;
    }

    return matrix->cont[row][col];
}

void set_elem(Matrix* matrix, int row, int col, double val)
{
    if (row >= matrix->row_num || col >= matrix->col_num) {
        printf("\nSetting element error:\nmatrix index out of range!\n");
    } else {
        matrix->cont[row][col] = val;
    }
}

int get_rows(Matrix* matrix)
{
    return matrix->row_num;
}

int get_cols(Matrix* matrix)
{
    return matrix->col_num;
}
