
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

//TODO
void free_matrix(Matrix* matrix)
{
    if (matrix != NULL)
    {
        for (int i = 0; i < matrix -> row; i++)
            free(matrix -> matr[i]);
        free(matrix -> matr);
        free(matrix);
    }
}


Matrix* create_matrix_from_file(FILE* file)
{
    int col, row;
    if ((fscanf(file, "%d", &row) == 0) || (fscanf(file, "%d", &col) == 0)) 
    {   
        printf("Ошибка в файле\n"); 
        return NULL;
    }
    Matrix *matr = create_matrix(row, col);
    if (matr == NULL) return NULL;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (fscanf(file, "%lf", &(matr -> matr[i][j])) == EOF)
            {
                printf("Ошибка в файле\n");
                free_matrix(matr);
                return NULL;
            }
    double d;
    if (fscanf(file, "%lf", &d) != EOF) return NULL;
    return matr;    
}

Matrix* create_matrix(int row, int col)
{
    Matrix *matr = malloc(sizeof(Matrix));
    matr -> row = row;
    matr -> col = col;
    matr -> matr = malloc(sizeof(double *) * row);
    for (int i = 0; i < row; i++)
        matr -> matr[i] = malloc(sizeof(double) * col);
    return matr;
}

double get_elem(Matrix* matrix, int row, int col)
{
    if((row < matrix -> row) && (col < matrix -> col)) 
        return matrix -> matr[row][col];
    printf("Границы выходят за приделы матрицы\n"); 
    return 0;
}

void set_elem(Matrix* matrix, int row, int col, double val)
{
    if((row < matrix -> row) && (col < matrix -> col)) 
        matrix -> matr[row][col] = val;
    else
        printf("Границы выходят за приделы матрицы\n"); 
}

int get_rows(Matrix* matrix)
{
    return matrix -> row;
}

int get_cols(Matrix* matrix)
{
    return matrix -> col;
}
