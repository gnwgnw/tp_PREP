#include "matrix.h"

Matrix* create_matrix_from_file(FILE* file) {
    int rowsCount = 0, columnsCount = 0;

    if (fscanf(file, "%11d\n%11d\n", &rowsCount, &columnsCount) != 2) {
        if (ferror(file)) {
            printf("File read error\n");
        } else {
            printf("Wrong file structure\n");
        }

        return NULL;
    }

    if (rowsCount <= 0) {
        printf("Wrong rows count\n");
        return NULL;
    } else if (columnsCount <= 0) {
        printf("Wrong columns count\n");
        return NULL;
    }

    struct Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rowsCount = (unsigned int)rowsCount;
    matrix->columnsCount = (unsigned int)columnsCount;
    matrix->map = calloc( sizeof(double *), rowsCount);

    for (unsigned int rowIndex = 0; rowIndex < rowsCount; ++rowIndex) {
        matrix->map[rowIndex] = calloc( sizeof(double), columnsCount);

        for (unsigned int columnIndex = 0; columnIndex < columnsCount; ++columnIndex) {
            double buffer;
            if (fscanf(file, "%lf", &buffer) != 1) {
                if (ferror(file)) {
                    printf("File read error\n");
                } else {
                    printf("Wrong file structure\n");
                }
                
                free_matrix(matrix);
                return NULL;
            }

            set_elem(matrix, rowIndex, columnIndex, buffer);
        }
    }

    return matrix;
}

Matrix* create_matrix(int row, int col) {
    struct Matrix *matrix = malloc(sizeof(Matrix));
    if (row <= 0) {
        printf("Wrong rows count\n");
        return NULL;
    } else if (col <= 0) {
        printf("Wrong columns count\n");
        return NULL;
    }

    matrix->rowsCount = (unsigned int)row;
    matrix->columnsCount = (unsigned int)col;

    matrix->map = calloc( sizeof(double *), row);
    for (unsigned int rowIndex = 0; rowIndex < row; ++rowIndex) {
        matrix->map[rowIndex] = calloc( sizeof(double), col);

        for (unsigned int columnIndex = 0; columnIndex < col; ++columnIndex) {
            set_elem(matrix, rowIndex, columnIndex, 0.0);
        }
    }

    return matrix;
}

void free_matrix(Matrix* matrix) {
    for (unsigned int i = 0; i < matrix->rowsCount; ++i) {
        free(matrix->map[i]);
    }

    free(matrix->map);
    free(matrix);
}

double get_elem(Matrix* matrix, int row, int col) {
    if (row < 0 || row >= get_rows(matrix)){
        printf("Wrong row index\n");
        return 0;
    } else if (col < 0 || col >= get_cols(matrix)) {
        printf("Wrong column index\n");
        return 0;
    } else {
        return matrix->map[row][col];
    }
}

void set_elem(Matrix* matrix, int row, int col, double val) {
    if (row < 0 || row >= get_rows(matrix)){
        printf("Wrong row index\n");
    } else if (col < 0 || col >= get_cols(matrix)) {
        printf("Wrong column index\n");
    } else {
        matrix->map[row][col] = val;
    }
}

int get_rows(Matrix* matrix) {
    return (int)matrix->rowsCount;
}

int get_cols(Matrix* matrix) {
    return (int)matrix->columnsCount;
}
