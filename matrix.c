#include <stdlib.h>
#include <ctype.h>
#include "matrix.h"

Matrix* create_matrix(const int row,const int col)
{
    Matrix* mat = NULL;
    mat = malloc(sizeof(Matrix));
    if (mat == NULL) {
        printf("Error memory allocation\n");
        free(mat);
        return NULL;
    }
    mat->rows = row;
    mat->cols = col;
    mat->arr = NULL;
    mat->arr = malloc(row*sizeof(double*));
    if (mat->arr == NULL) {
        printf("Error memory allocation\n");
        free(mat->arr);
        free(mat);
        return NULL;
    }
    for (int i = 0; i < row; i++) {
        mat->arr[i] = NULL;
        mat->arr[i] = malloc(col*sizeof(double));
        if (mat->arr[i] == NULL) {
            printf("Error memory allocation\n");
            for (int k=0; k<i; k++) {
                free(mat->arr[k]);
            }
            free(mat->arr);
            free(mat);
            return NULL;
    }
    }
    return mat;
}

void free_matrix(Matrix* matrix) {
    for (int i = 0; i < get_rows(matrix); i++)
        free(matrix->arr[i]);
    free (matrix->arr);
    free (matrix);
}

static int err_sruct(Matrix* matrix) {
    if (!matrix) {
        printf("error in the transmitted structure\n");
        return 1;
    }
    return 0;
}

int get_rows(Matrix* matrix) {
    if (err_sruct(matrix))
        return -1;
    return matrix->rows;
}

int get_cols(Matrix* matrix) {
    if (err_sruct(matrix))
        return -1;
    return matrix->cols;
}

double get_elem(Matrix* matrix, const int row, const int col) {
    return matrix->arr[row][col];
}

void set_elem(Matrix* matrix,const int row, const int col,const double val) {
    matrix->arr[row][col] = val;
}

static void err_type_of_data(Matrix *matrix,FILE* file) {
    printf("Incorrect type of data storage in file.\n");
    free_matrix(matrix);
    fclose(file);
    exit(EXIT_FAILURE);
}

static void err_array_size(FILE* file) {
    printf("Incorrect array size.\n");
    fclose(file);
    exit(EXIT_FAILURE);
}

static int check_in_file_extra_characters(FILE *file) {
    fseek(file,0,SEEK_SET);
    int ch = getc(file);
    int count_p = 0;
    while (ch != EOF)
    {
        if (isgraph(ch) && !isdigit(ch) && (ch != '.') && (ch != '-'))
        {
            printf("In the file found invalid character.\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        if (ch == '\n')
            count_p ++;
        ch = getc(file);

    }
    return count_p;
}

static void zeroing(Matrix* m) {
    for (int i = 0; i < get_rows(m); i++) {
        for (int j = 0; j < get_cols(m); j++) {
            set_elem(m,i,j,0);
        }
    }
}

Matrix *create_matrix_from_file(FILE* file) {
    int count_elem = check_in_file_extra_characters(file);
    fseek(file,0,SEEK_SET);
    int row = 0, col = 0;
    int count_nonzero;
    if(!fscanf(file, "%d %d %d", &row,&col,&count_nonzero) == 1)
        err_array_size(file);
    if ((row < 0) || (col < 0) || (count_nonzero < 0))
        err_array_size(file);
    Matrix *matrix = NULL;
    matrix = create_matrix(row,col);
    if(!matrix) {
        printf("Error memory allocation.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    zeroing(matrix);
    count_elem -= 3;
    if (count_nonzero != count_elem) {
        err_type_of_data(matrix,file);
    }
    int i_ind = 0,j_ind = 0;
    double data;
    for (int i = 0; i < count_nonzero; i++) {
        if (!fscanf(file,"%d %d %lf", &i_ind,&j_ind,&data) == 1)
            err_type_of_data(matrix,file);
        if ((i_ind < 0) || (j_ind < 0))
            err_type_of_data(matrix,file);
        set_elem(matrix,i_ind,j_ind,data);
    }
    return matrix;
}


