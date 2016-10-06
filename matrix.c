#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "matrix.h"

Matrix* create_matrix(int row, int col)
{
    if(row <= 0 || col <= 0)
        return NULL;

    Matrix *mtrx = malloc(sizeof(Matrix));
    if(mtrx == NULL)
        return NULL;

    mtrx->ptr = malloc(sizeof(double *) * row);
    if(mtrx == NULL)
        return NULL;

    for(int i = 0; i < row; i++)
    {
        mtrx->ptr[i] = calloc(sizeof(double), col);
        if(mtrx->ptr[i] == NULL)
        {
            for(int j = 0; j < i; j++)
                free(mtrx->ptr[j]);
            free(mtrx->ptr);
            return NULL;
        }
    }

    mtrx->col = col;
    mtrx->row = row;

    return mtrx;
}

Matrix* create_matrix_from_file(FILE* file)
{
    if(file == NULL)
        return NULL;

    int row = 0;
    if(fscanf(file, "%d", &row) != 1)
        return NULL;

    int col = 0;
    if(fscanf(file, "%d", &col) != 1)
        return NULL;

    int num = 0;
    if(fscanf(file, "%d", &num) != 1)
        return NULL;

    Matrix *mtrx = create_matrix(row, col);
    if(mtrx == NULL)
        return NULL;

    // Проверим, в каком формате записан файл
    rewind(file);
    int temp;
    fscanf(file, "%d", &temp);
    fscanf(file, "%d", &temp);
    while( fgetc(file) != '\n');
    char str[80];
    fgets(str, 80, file);
    int count = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            if(i == 0)
                count++;
            else if (i > 0 && isspace(str[i-1]) )
                count++;
        }
    }

    if( (count == 1) && num != 0 && !feof(file))
    {
        double tmp = 0;
        int i = 0;
        while( (fscanf(file, "%d", &row) == 1) && (fscanf(file, "%d", &col) == 1) && (fscanf(file, "%lf", &tmp) == 1) && (i < num) )
        {
            set_elem(mtrx, row, col, tmp);
            i++;
        }
    }
    else
    {
        rewind(file);
        fscanf(file, "%d", &temp);
        fscanf(file, "%d", &temp);
        double tmp = 0;
        for(int i = 0; i < row; i++)
            for(int j = 0; j < row; j++)
            {
                fscanf(file, "%lf", &tmp);
                set_elem(mtrx, i, j, tmp);
            }
    }

    return mtrx;
}

void free_matrix(Matrix* matrix)
{
    if(matrix == NULL)
        return;

    for(int i = 0; i < matrix->row; i++)
        free(matrix->ptr[i]);

    free(matrix->ptr);

    matrix->row = 0;
    matrix->col = 0;
    free(matrix);
}

double get_elem(Matrix* matrix, int row, int col)
{
    // Не самая удачная реализация, так как в случае таких себе вводных параметров
    // Мы никогда не узнаем, что получили такой себе ответ, а не настоящий элемент матрицы
    if(matrix == NULL || row < 0 || col < 0 || row >= matrix->row || col >= matrix->col)
        return 0;

    return matrix->ptr[row][col];
}

void set_elem(Matrix* matrix, int row, int col, double val)
{
    if(matrix == NULL || row < 0 || row >= matrix->row || col < 0 || col >= matrix->col)
        return;

    matrix->ptr[row][col] = val;
}

int get_rows(Matrix* matrix)
{
    if(matrix == NULL)
        return 0;

    return matrix->row;
}

int get_cols(Matrix* matrix)
{
    if(matrix == NULL)
        return 0;

    return matrix->col;
}
