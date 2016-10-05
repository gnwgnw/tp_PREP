#include <stdlib.h>
#include "matrix.h"

#define SIZE 64

int assert(int assertion, char* message) {
    if (assertion == 0) {
        printf("%s\n", message);
        return 1;
    }
    return 0;
}

Matrix* multiply(Matrix* matrix_1, Matrix* matrix_2) {
    
    if (assert(matrix_1->col == matrix_2->row, "Matrices have incorrect dimensions. matrix_1->col != matrix_2->row")) return NULL;

    Matrix* res_matrix = create_matrix(matrix_1->row, matrix_2->col);
    double tmp = 0;
    int c = 0;
    int i = 0;

    for (c = 0; c < res_matrix->col * res_matrix->row; ++c) {
        tmp = 0;
        for (i = c; i - c < matrix_1->col; ++i)
            tmp += matrix_1->data[i -c + (c / matrix_2->row) * matrix_1->row] * matrix_2->data[(c % matrix_2->row) + ((i - c) * matrix_2->row)];

        res_matrix->data[c] = tmp;
    }
    return (res_matrix);
}
   
Matrix* create_matrix_from_file(FILE* file) {
    int scan_test = 0;
    if (file) {
        int r_num = 0, c_num = 0, itom = 0;
        scan_test = fscanf(file, "%1d", &r_num);
	if (assert(scan_test == 1 && r_num > 0, "Invalid input.")) return NULL;
        if (assert(scan_test != EOF, "Failed to read from file.")) return NULL;
        scan_test = fscanf(file, "%1d", &c_num);
        if (assert(scan_test == 1 && c_num > 0, "Invalid input.")) return NULL;
        if (assert(scan_test != EOF, "Failed to read from file.")) return NULL;
        scan_test = fscanf(file, "%d", &itom);
        if (assert(scan_test == 1 && itom > 0, "Invalid input.")) return NULL;
        if (assert(scan_test != EOF, "Failed to read from file.")) return NULL;

        if (assert(r_num * c_num >= itom, "Too many items in file.")) return NULL;

        Matrix* mfile = create_matrix(r_num, c_num);

        if (!mfile)
            return NULL;

        int i = 0, r = 0, c = 0;
        double val = 0;
        for (i = 0; i < itom; ++i) {
            scan_test = fscanf(file, "%d %d %lf", &r, &c, &val);
            if (assert(scan_test == 3 && r >= 0 && c >= 0, "Invalid input.")) return NULL;
            if (assert(scan_test != EOF, "Failed to read from file. File is incomplete.")) return NULL;
            set_elem(mfile, r, c, val);
        }
        return mfile;
    }
    else {
        printf("%s", "ERROR: file can not be opened" );
        return NULL;
    }
}

Matrix* create_matrix(int row, int col) {
    if (assert(row > 0 && col > 0, "New matrix must be at least a 1 by 1")) return NULL;
    Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->col = col;
    matrix->row = row;
    matrix->data = (double*) malloc(col * row * sizeof(double));

    int i = 0, j = 0;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j)
            set_elem(matrix, i, j, 0.);
    }
    return matrix;
}

double get_elem(Matrix* matrix, int row, int col) {
    return matrix->data[row * matrix->col + col];
}

void set_elem(Matrix* matrix, int row, int col, double val) {
    matrix->data[row * matrix->col + col] = val;
}

void free_matrix(Matrix* matrix) {
    if (matrix != NULL) {
        if (matrix->data != NULL) {
            free(matrix->data);
            matrix->data = NULL;
        }

        free(matrix);
        matrix = NULL;
    }
    return;
}

int get_rows(Matrix* matrix) {
    return matrix->row;
}

int get_cols(Matrix* matrix) {
    return matrix->col;
}

void display(Matrix* matrix) {
    int i = 0, j = 0;
    double* ptr = matrix->data;
    for (i = 0; i < matrix->row; ++i) {
        for (j = 0; j < matrix->col; ++j) {
            printf("%lf ", *(ptr++));
        }
        printf("\n");
    }
    return;
}

void copy_matrix(Matrix* matrix1, Matrix* matrix2) {
    matrix1->row = matrix2->row;
    matrix1->col = matrix2->col;
    int i = 0, elements = get_rows(matrix2) * get_cols(matrix2);
    for (; i < elements; ++i)
        matrix1->data[i] = matrix2->data[i];
    return;
}
