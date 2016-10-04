//
// Created by Pasha on 02.10.2016.
//
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>
#include "matrix.h"

static  void read_int_value(FILE *f, int *val);
static  void read_double_value(FILE *f, double *val);
static void read_matrix_from_file(FILE *file, Matrix *my_matrix, int number_of_row, int number_of_col, int number_of_not_zero);
static double calculate_l_norma(double  **matrix, int number_of_row, int number_of_col);
static void error_exit(Matrix *matrix);
static void set_zero_value(Matrix *matrix, int row, int col);

Matrix* create_matrix_from_file(FILE* file){
    Matrix *my_matrix;
    int number_of_col, number_of_row, number_of_not_zero;
    int ch;

    read_int_value(file, &number_of_col);
    read_int_value(file, &number_of_row);
    read_int_value(file, &number_of_not_zero);
    if ((ch = fgetc(file)) != '\n' ){
        fprintf(stderr, "unknow type of input data  \n");
        exit(2);
    }
    my_matrix = create_matrix(number_of_row, number_of_col);
    read_matrix_from_file(file, my_matrix, number_of_row, number_of_col, number_of_not_zero);
    double result = calculate_l_norma(my_matrix->matrix, number_of_row, number_of_col);

    return  my_matrix;
}

static double calculate_l_norma(double  **matrix, int number_of_row, int number_of_col){
    double max = 0, result = 0;
    for (int i = 0; i < number_of_row; i++){
        for (int j = 0; j < number_of_col; j++){
            result += fabs(matrix[j][i]);
        }
        if (result > max){
            max = result;
        }
        result = 0;
        printf("\n");
    }
    // printf("%lf \n", max);
    return max;
}

static void read_matrix_from_file(FILE *file, Matrix *my_matrix, int number_of_row, int number_of_col, int number_of_not_zero){
    int row, col;
    double  value;
    int i = 0;
    while(fscanf(file,"%d", &row) == 1){
        if(row < 1 || row >= number_of_row){
            error_exit(my_matrix);
        }
        if(fscanf(file,"%d", &col) == 1){
            if(col < 1 || col >= number_of_col){
                error_exit(my_matrix);
            }
            if(fscanf(file,"%lf", &value) == 1){
                my_matrix->matrix[row-1][col-1] = value;
                i++;
            }
            else {
                error_exit(my_matrix);
            }
        }
        else {
            error_exit(my_matrix);
        }
    }
    if (i != number_of_not_zero){
        error_exit(my_matrix);
    }

}

static void error_exit(Matrix *matrix){
    fprintf(stderr, "error in input data \n");
    free_matrix(matrix);
    exit(3);
}

Matrix* create_matrix(int row, int col){
    Matrix *my_matrix = (Matrix *)malloc(sizeof(Matrix));

    my_matrix->matrix = (double**)malloc(sizeof(double*)*row);
    assert(my_matrix->matrix);
    for (int i= 0; i < row; i++){
        my_matrix->matrix[i] = (double*)malloc(sizeof(double)*col);
        assert(my_matrix->matrix);
    }
    my_matrix->number_of_row = row;
    my_matrix->number_of_col = col;
    set_zero_value(my_matrix,row,col);
    return  my_matrix;
}

static void set_zero_value(Matrix *matrix, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            matrix->matrix[i][j] = 0;
        }
    }
}

void free_matrix(Matrix* matrix){
    for (int i= 0; i < matrix->number_of_row; i++){
        free(matrix->matrix[i]);
    }
}

int get_rows(Matrix* matrix){
    return  matrix->number_of_row;
}

int get_cols(Matrix* matrix){
    return matrix->number_of_col;
}

double get_elem(Matrix* matrix, int row, int col){
    assert(row <= matrix->number_of_row || col <= matrix->number_of_col);
    return matrix->matrix[row-1][col-1];
}

void set_elem(Matrix* matrix, int row, int col, double val){
    assert(row <= matrix->number_of_row || col <= matrix->number_of_col);
    matrix->matrix[row-1][col-1] = val;
}


static  void read_int_value(FILE *f, int *val){
    int k = 0;
    if((k = fscanf(f, "%d", val)) != 1){
        fprintf(stderr, "unknow type of data \n");
        exit(1);
    }

    if (k == EOF){
        fprintf(stderr, "can't read int value \"%d\"\n", k);
        exit(1);
    }
}

static  void read_double_value(FILE *f, double *val){
    int k = 0;
    if((k = fscanf(f, "%lf", val)) != 1){
        fprintf(stderr, "unknow type of data \n");
        exit(1);
    }
    if (k == EOF){
        fprintf(stderr, "can't read double value \"%d\"\n", k);
        exit(1);
    }
}