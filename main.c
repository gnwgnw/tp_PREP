#include <stdio.h>
#include <math.h>

#include "matrix.h"

double getEuclideanNorm(Matrix *matrix);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("homework2 [filename]\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File \"%s\" is not found\n", argv[1]);
        return 2;
    }

    Matrix *matrix = create_matrix_from_file(file);
    fclose(file);

    if (matrix) {
        printf("%lf\n", getEuclideanNorm(matrix));
        free_matrix(matrix);
        return 0;
    } else {
        return 3;
    }
}

double getEuclideanNorm(Matrix *matrix) {
    double squaresSum = 0;

    for (unsigned int i = 0; i < matrix->rowsCount; ++i) {
        for (unsigned int j = 0; j < matrix->columnsCount; ++j) {
            squaresSum += pow(matrix->map[i][j], 2);
        }
    }

    return sqrt(squaresSum);
}
