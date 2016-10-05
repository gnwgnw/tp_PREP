#include "matrix.h"
#include <malloc.h>
#include <stdlib.h>


Matrix* create_matrix_from_file(FILE* file)
    {
      if (file == NULL)
      {
        printf("Invalid file. Please, try another file.");
        exit(EXIT_FAILURE);
      }
    int rows, cols;
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
       printf("Incorrect format of file");
       exit(EXIT_FAILURE);
    }
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix->rows = row;
    matrix->cols = col;
    matrix->elem = malloc(row * sizeof(double*));
    for (int i = 0; i < row; ++i)
    {
        matrix->elem[i] = malloc(col * sizeof(double));
    }
    return matrix; 
    }

void free_matrix(Matrix* matrix)
    {
     for (int i = 0; i < matrix->rows; ++i)    
        free(matrix->elem[i]);
      
      free(matrix->elem);
      free(matrix);
    }

double get_elem(Matrix* matrix, int row, int col)
    {
      if (col<0 || row<0) printf("Invalid rows or cols number.");
      else
      return matrix->elem[row][col];
    }

void set_elem(Matrix* matrix, int row, int col, double val)
    {
      if (col<0 || row<0) printf("Invalid rows or cols number.");
      else
      matrix->elem[row][col]=val;
    }

int get_rows(Matrix* matrix)
    {
      return matrix->rows;
    }

int get_cols(Matrix* matrix)
    {
      return matrix->cols;
    }
