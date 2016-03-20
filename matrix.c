#include "matrix.h"
#include <malloc.h>

Matrix* create_matrix_from_file(FILE* file)
{
    int rows = 0;
    int cols = 0;
    fscanf(file, "%d%d", &rows, &cols);
    Matrix* matrix = create_matrix(rows, cols);
    double val = 0.0;
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            fscanf(file, "%lf", &val);
            set_elem(matrix, i, j, val);
        }
    }
    return matrix;
}

Matrix* create_matrix(int row, int col)
{
    Matrix matrix;
    Matrix* pMatrix = &matrix;
    pMatrix->rows = row;
    pMatrix->cols = col;
    pMatrix->items = malloc(row * sizeof(double*));
    int i;
    for (i = 0; i < row; i++)
    {
        pMatrix->items[i] = malloc(col * sizeof(double));
    }
    return pMatrix;
}

void free_matrix(Matrix* matrix)
{
    int i;
    for (i = 0; i < matrix->rows; i++)
    {
        free(matrix->items[i]);
    }
    free(matrix->items);
}

double get_elem(Matrix* matrix, int row, int col)
{
    return matrix->items[row][col];
}

void set_elem(Matrix* matrix, int row, int col, double val)
{
    matrix->items[row][col] = val;
}
