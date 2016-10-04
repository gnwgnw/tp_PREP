#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "additionmatrix.h"

void print_Matrix(Matrix* m) {
    for (int i = 0; i < get_rows(m); i++) {
        for (int j = 0; j < get_cols(m); j++) {
            printf("%.2lf\t ",get_elem(m,i,j));
        }
        printf("\n");
    }
}

double get_euclidean_norm (Matrix *m) {
    double buff = 0;
    for (int i = 0; i < get_rows(m); i++) {
        for (int j = 0; j < get_cols(m); j++) {
            buff += pow(fabs(get_elem(m, i, j)),2);
        }
    }
    return sqrt(buff);
}
