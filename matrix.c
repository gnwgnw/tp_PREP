#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix* create_matrix(int row, int col)
{
    Matrix* matrix = calloc(row*col,sizeof(Matrix));
    if(matrix ==NULL)
    {
        printf("Not enough memory!\n");
        exit(1);
    }
    return matrix;
}
double get_l_norm(Matrix *matrix, int row, int col)
{
    int i, j, col_n;
    double temp_l_max = 0;
    double l_norma_max = 0;
    for(i = 0; i<col; i++)
    {
        temp_l_max = 0;
        for(j = i; j<row*col; j++)
        {
            if(matrix[i].col == matrix[j].col)
            {
                if(matrix[j].value < 0)
                {
                    temp_l_max +=matrix[j].value*(-1);
                }
                else
                temp_l_max +=matrix[j].value;
            }
        }
        if(l_norma_max<temp_l_max)
        {
            col_n = i;
            l_norma_max = temp_l_max;
        }
    }
    printf("\nl-norm of given Matrix is %.02f (in col[%i])\n", l_norma_max, col_n);
    return l_norma_max;
}

Matrix* create_matrix_from_file(FILE* file)
{
    int i, j,k, row, col;
    if(file == NULL)
    {
        printf("Can not open file");
        exit(0);
    }
    else
    {
        int fSpace = 1, nCount = 0;
        char ch[2]= {0};
        while(! feof(file))
        {
            fgets(ch ,2, file);
            if(ch[0] > 41)
                fSpace = 0;
            else if( fSpace ==0)
            {
                nCount++;
                fSpace = 1;
            }
            ch[0] = 0;
        }
        fseek(file , 0 , SEEK_END);
        long lSize = ftell(file);
        rewind (file);
        double buff[nCount];
        for(i = 0; i<nCount; i++)
        {
          if(fscanf(file, "%lf", &buff[i]) !=1)
          {
              printf("Incorrect matrix elements");
              exit(0);
          }
        }
        if((buff[0] - (int)buff[0] != 0)||(buff[1] - (int)buff[1] != 0))
        {
            printf("N. of rows and cols must be an integer");
            exit(0);
        }
        else
        {
            row = buff[0];
            col = buff[1];
        }
        if(row*col != nCount -2)
        {
            printf("Wrong number of elements");
            exit(0);
        }

        printf("\n*************\n");
        Matrix *matrix = create_matrix(row, col);
        j = 0;
        i = 0;
        matrix[0].cols = col;
        matrix[0].rows = row;
        for(k = 2; k< row*col+2; k++)
        {
            matrix[k-2].value = buff[k];
            matrix[k-2].row = i;
            matrix[k-2].col = j;
            j++;
            if(j==col)
            {
                i++;
                j = 0;
            }
        }
        fclose(file);
        get_l_norm(matrix, row, col);
       return matrix;
    }

}

void set_elem(Matrix* matrix, int row, int col, double val)
{
    int i;
    for(i = 0; i<row*col; i++)
    {
        if((matrix[i].col ==col)&&(matrix[i].row ==row))
            matrix[i].value = val;
    }
}

double get_elem(Matrix* matrix, int row, int col)
{
    double elem;
    int i;
    for(i = 0; i<col*row; i++)
    {
        if((matrix[i].col ==col)&&(matrix[i].row ==row))
            elem = matrix[i].value;
        else printf("Element with these coordinates doesn't exist");
    }
    return elem;
}

int get_rows(Matrix* matrix)
{
    int rows = matrix[0].rows;
    return rows;
}

int get_cols(Matrix* matrix)
{
    int cols = matrix[0].cols;
    return cols;
}
void free_matrix(Matrix* matrix)
{
    free(matrix);
}
