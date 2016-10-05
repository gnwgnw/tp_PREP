#include "matrix.h"

Matrix* create_matrix_from_file(FILE* file){

    int row, col;
    Matrix* matrix;

    if(fscanf(file, "%d%d", &row, &col) != 2){
        fprintf(stderr, "No info about number of rows/columns. Check file.\n");
        return NULL;
    }

    matrix = create_matrix(row, col);

    if(!matrix){
        fprintf(stderr, "Can not allocate memory for matrix.\n");
        return NULL;
    }

    double val;
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++){
            if(fscanf(file, "%lf", &val) != 1){
                fprintf(stderr, "Your file contains incorrect elements or has too few of them.\n");
                return NULL;
            }
            set_elem(matrix, i, j, val);
        }

    return matrix;
}

Matrix* create_matrix(int row, int col){

    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));

    matrix->row = row;
    matrix->col = col;

    matrix->elems = calloc(row * col, sizeof(Element));

    return matrix;
}

void free_matrix(Matrix* matrix){

    free(matrix->elems);
    free(matrix);
}

double get_elem(Matrix* matrix, int row, int col){

    int pos = get_cols(matrix) * row + col;
    return matrix->elems[pos].elem;
}

void set_elem(Matrix* matrix, int row, int col, double val){

    int pos = get_cols(matrix) * row + col;
    matrix->elems[pos].elem = val;
    matrix->elems[pos].row_ind = row;
    matrix->elems[pos].col_ind = col;
}

int get_rows(Matrix* matrix){
    return matrix->row;
}

int get_cols(Matrix* matrix){
    return matrix->col;
}
