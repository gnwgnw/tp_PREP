//Барсуков Сергей


#include "matrix.h"
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Enter the name of matrix file\n");
        return EXIT_FAILURE;
    }

    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error! File is not open\n");
        return EXIT_FAILURE;
    }

    Matrix *myMatrix;
    myMatrix = create_matrix_from_file(file);

    fclose(file);
    if (myMatrix == NULL || get_cols(myMatrix) < 0 || get_rows(myMatrix) < 0) {
        printf("Error!Incorrectly created matrix\n");
        free_matrix(myMatrix);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < get_cols(myMatrix); i++) {
        for (int j = 0; j < get_rows(myMatrix); j++) {
            double elem = get_elem(myMatrix, j, i);
            printf("%.2lf  ", elem);
        }
        printf("\n");
    }

    free_matrix(myMatrix);

    return EXIT_SUCCESS;
}