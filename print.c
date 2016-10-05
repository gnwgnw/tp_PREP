#include "matrix.h"
#include "print.h"

int correct_data(Matrix* first_matrix, Matrix* second_matrix){
    return(get_cols(first_matrix) == get_rows(second_matrix));
}

void print_matrix(Matrix* matrix){

    int row = get_rows(matrix);
    int col = get_cols(matrix);
    double val;

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            val = get_elem(matrix, i, j);
            printf("%6.2lf ", val);
        }
        printf("\n");
    }
}

void print_result(Matrix* first_matrix, Matrix* second_matrix){

    int first_row = get_rows(first_matrix);
    int second_row = get_rows(second_matrix);
    int second_col = get_cols(second_matrix);

    double val1, val2, valres;
    for(int i = 0; i < first_row; i++){
        for(int j = 0; j < second_col; j++){
            valres = 0;
            for(int k = 0; k < second_row; k++){
                val1 = get_elem(first_matrix, i, k);
                val2 = get_elem(second_matrix, k, j);
                valres += val1 * val2;
            }
            printf("%6.2lf ", valres);
        }
        printf("\n");
    }
}
