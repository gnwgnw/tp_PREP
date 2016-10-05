#include "matrix.h"

typedef enum{
    WRONG_NUMBER_OF_ARGUMENTS = 1,
    WRONG_FILENAME,
    CAN_NOT_CREATE_MATRIX,
    CAN_NOT_MULTIPLY
} error_t;

void print_matrix(Matrix* matrix);
void print_result(Matrix* first_matrix, Matrix* second_matrix);
int correct_data(Matrix* first_matrix, Matrix* second_matrix);


int main(int argc, char* argv[]){

    error_t error;

    const int correct_argc = 3;

    if(argc != correct_argc){
        fprintf(stderr, "Wrong number of arguments. You entered %d. Must be %d.\n", argc, correct_argc);
        return error = WRONG_NUMBER_OF_ARGUMENTS;
    }


    FILE* file1 = fopen(argv[1], "r");

    if(!file1){
        fprintf(stderr, "Can not open '%s'.\n", argv[1]);
        return error = WRONG_FILENAME;
    }

    Matrix* first_matrix = create_matrix_from_file(file1);
    if(!first_matrix){
        fprintf(stderr, "Can not create first matrix from file '%s'.\n", argv[1]);
        fclose(file1);
        return error = CAN_NOT_CREATE_MATRIX;
    }
    fclose(file1);

    printf("First matrix:\n--------------\n");
    print_matrix(first_matrix);
    printf("\n");

    FILE* file2 = fopen(argv[2], "r");

    if(!file2){
        fprintf(stderr, "Can not open '%s'.\n", argv[2]);
        return error = WRONG_FILENAME;
    }

    Matrix* second_matrix = create_matrix_from_file(file2);
    if(!second_matrix){
        fprintf(stderr, "Can not create second matrix from file '%s'.\n", argv[2]);
        fclose(file2);
        free_matrix(first_matrix);
        return error = CAN_NOT_CREATE_MATRIX;
    }

    fclose(file2);

    printf("Second matrix:\n--------------\n");
    print_matrix(second_matrix);
    printf("\n");

    if(!correct_data(first_matrix, second_matrix)){
        fprintf(stderr,
                "Can not multiply. Number of cols in first matrix != number of columns in second matrix");
       free_matrix(first_matrix);
       free_matrix(second_matrix);
       return error = CAN_NOT_MULTIPLY;
    }

    printf("Resulting matrix:\n-----------------\n");
    print_result(first_matrix, second_matrix);
    printf("\n");

    free_matrix(first_matrix);
    free_matrix(second_matrix);

    return 0;
}

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

