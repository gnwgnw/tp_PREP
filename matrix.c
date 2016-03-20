#include "matrix.h"
#include <malloc.h>

Matrix* create_matrix_from_file(FILE* file)
{
    if (file == NULL)
    {
        return NULL;
    }
    int rows = 0;
    int cols = 0;
    fscanf(file, "%d%d", &rows, &cols);
    
    Matrix* matrix = create_matrix(rows, cols);
    
    double val = 0.0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(file, "%lf", &val);
            set_elem(matrix, i, j, val);
        }
    }
    
    return matrix;
}

Matrix* create_matrix(int row, int col)
{
    if (row <= 0 || col <= 0)
    {
        return NULL;
    }
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix->rows = row;
    matrix->cols = col;
    matrix->items = malloc(row * sizeof(double*));
    for (int i = 0; i < row; i++)
    {
        matrix->items[i] = malloc(col * sizeof(double));
    }
    return matrix;
}

void free_matrix(Matrix* matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        free(matrix->items[i]);
    }
    free(matrix->items);
    free(matrix);
}

double get_elem(Matrix* matrix, int row, int col)
{
    if (row < 0)
    {
        row = 0;
    }
    if (col < 0)
    {
        col = 0;
    }
    return matrix->items[row][col];
}

void set_elem(Matrix* matrix, int row, int col, double val)
{
    if (row < 0)
    {
        row = 0;
    }
    if (col < 0)
    {
        col = 0;
    }
    matrix->items[row][col] = val;
}

int get_rows(Matrix* matrix)
{
    return matrix->rows;
}

int get_cols(Matrix* matrix)
{
    return matrix->cols;
}
