#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "additionmatrix.h"

int isFileOpenAndNotEmpty(FILE *file) {
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    int ch = getc(file);
    if (ch == EOF) {
        printf("File is empty.\n");
        fclose(file);
        return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error arguments\n");
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1],"r");
    if(!isFileOpenAndNotEmpty(file))
        return EXIT_FAILURE;
    Matrix* p = create_matrix_from_file(file);
    printf("Matrix:\n");
    print_Matrix(p);
    printf("Euclidean norm: %lf\n", get_euclidean_norm(p));
    fclose(file);
    free_matrix(p);
    return EXIT_SUCCESS;
}
