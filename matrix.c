#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <math.h>

const double precision = 1e-3;

Matrix *create_matrix_from_file(FILE *file) {
   
    
    Matrix *array = malloc(sizeof(Matrix));

    if (array == NULL) {
         fprintf(stderr, "Memory error!\n");
         abort();
    }
    array->matr = NULL;

    if (fscanf(file, "%d\n%d", &array->rows, &array->cols) < 2) {
        fprintf(stderr, "Error! Incorrect file!\n");
        free(array);
        fclose(file);
        abort();
    }

    int rows = get_rows(array);
    int cols = get_cols(array);

    if (rows < 1  || cols < 1) {
        fprintf(stderr, "Rows or columns must be positive!\n");
        free(array);
        fclose(file);
        abort();
    }

    array->matr = (double**)malloc(rows * sizeof(double*));

    for(int i = 0; i < rows; ++i)
        array->matr[i] = (double*)malloc(cols * sizeof(double));

    for(int i = 0; i < rows; ++i) {

        for(int j = 0; j < cols; ++j) {
                double temp;
                fscanf(file, "%lf", &temp);
                set_elem(array, i, j, temp);
            if (j != cols - 1 && fgetc(file) == '\n') {
                fprintf(stderr, "Incorrect matrix! Error in %d row\n", i+1);
                free_matrix(array);
                fclose(file);
                abort();
            }
        }
        if (fgetc(file) != '\n') {
            fprintf(stderr, "Incorrect matrix! Error in %d row\n", i+1);
            free_matrix(array);
            fclose(file);
            abort();
        }
    }
    fclose(file);
return array;
}

Matrix *create_matrix(int row, int col) {
    Matrix *array = malloc(sizeof(Matrix));
    array->matr = NULL;
    array->rows = row;
    array->cols = col;
    array->matr = (double**)malloc(row * sizeof(double*));

    for(int i = 0; i < row; ++i) {
        array->matr[i] = (double*)calloc(col,  sizeof(double));
    }
    return array;
}

Matrix *transpose(Matrix *matrix) {
   
    Matrix *array = create_matrix(get_cols(matrix), get_rows(matrix));

    int rows = get_rows(array);
    int cols = get_cols(array);

    for(int i = 0; i < get_rows(matrix); ++i)
        for(int j = 0; j < get_cols(matrix); ++j)
            set_elem(array, j, i, get_elem(matrix, i, j));
    return array;
}

/*Matrix *add_row(Matrix *matrix) {

}*/

void free_matrix(Matrix* matrix) {
    int rows = get_rows(matrix);

    for(int i = 0; i < rows; ++i)
    {
        free(matrix->matr[i]);
    }
    free(matrix->matr);
    free(matrix);
}

void set_elem(Matrix* matrix, int row, int col, double val) {
    matrix->matr[row][col] = val;
}

void print_matrix(Matrix *matrix) {
    int rows = get_rows(matrix);
    int cols = get_cols(matrix);


    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j)
            printf("%8.3lf ", get_elem(matrix, i, j));
    printf("\n");
    }
    printf("\n");
}

int get_rows(Matrix* matrix) {
    return matrix->rows;
}

int get_cols(Matrix* matrix) {
    return matrix->cols;
}

double get_elem(Matrix* matrix, int row, int col) {
    return matrix->matr[row][col];
}

double l_norm(Matrix* matrix) {

    double max = 0;
    double sum = 0;
    int rows = get_rows(matrix);
    int cols = get_cols(matrix);

    for(int i = 0; i < cols; ++i) {
        for(int j = 0; j < rows; ++j)
            sum += fabs(get_elem(matrix, j, i));
        if ((sum - max) > precision) {
            max = sum;
            sum = 0;
        }
    }

    return max;
}

double max_norm(Matrix* matrix) {
    double max = 0;
    double sum = 0;
    int rows = get_rows(matrix);
    int cols = get_cols(matrix);

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j)
            sum += fabs(get_elem(matrix, i, j));
        if ((sum - max) > precision) {
            max = sum;
            sum = 0;
        }
    }

    return max;
}

double e_norm(Matrix* matrix) {
    double sum = 0;

    int rows = get_rows(matrix);
    int cols = get_cols(matrix);

    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            sum += pow(fabs(get_elem(matrix, i, j)), 2.0);

    return pow(sum, 0.5);
}
