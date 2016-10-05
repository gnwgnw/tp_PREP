#include "matrix.h"
#include "print.h"

typedef enum{
    WRONG_NUMBER_OF_ARGUMENTS = 1,
    WRONG_FILENAME,
    CAN_NOT_CREATE_MATRIX,
    CAN_NOT_MULTIPLY
} error_t;

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
