//Барсуков Сергей


#include <stdlib.h>
#include <string.h>
#include "matrix.h"


static void ErrorExit() {
    printf("Error! Matrix is not created. Invalid data in the file\n");
    exit(EXIT_FAILURE);
}


Matrix *create_matrix_from_file(FILE *file) {

    if (file == NULL) {
        printf("Error! File is not open\n");
        exit(EXIT_FAILURE);
    }

    Matrix *myMatrix;
    int numberOfNonZeroElements;
    int row;
    int col;
    char *checkPtr;
    char buffer[1000000];

    if (fscanf(file, "%[^\n]s", buffer) != 1) {
        ErrorExit;
    }

    row = strtol(buffer, &checkPtr, 10);

    if (strlen(checkPtr) != 0) {
        printf("Warning!: file contains extra characters: %s\nThe Matrix could be done wrong!\n\n", checkPtr);
    }
    if (row <= 0) {
        ErrorExit();
    }
    fgetc(file);

    if (fscanf(file, "%[^\n]s", buffer) != 1) {
        ErrorExit();
    }

    checkPtr = NULL;
    col = strtol(buffer, &checkPtr, 10);

    if (strlen(checkPtr) != 0) {
        printf("Warning!: file contains extra characters: %s\nThe Matrix could be done wrong!\n\n", checkPtr);
    }
    if (col <= 0) {
        ErrorExit();
    }
    fgetc(file);

    if (fscanf(file, "%[^\n]s", buffer) != 1) {
        ErrorExit();
    }

    myMatrix = create_matrix(row, col);
    char *ptrWord = strstr(buffer, " ");
    if (ptrWord == NULL && col != 1) {

        numberOfNonZeroElements = strtol(buffer, 0, 10);;
        if (numberOfNonZeroElements < 0) {
            ErrorExit();
        }

        fgetc(file);

        for (int i = 0; i < numberOfNonZeroElements; i++) {
            int rowNumber;
            int colNumber;
            double element;
            ptrWord = buffer;
            checkPtr = ptrWord;
            if (fscanf(file, "%[^\n]s", buffer) != 1) {
                ErrorExit;
            }
            rowNumber = strtol(ptrWord, &checkPtr, 10);
            if (ptrWord == checkPtr) {
                ErrorExit();
            }

            ptrWord = checkPtr;
            colNumber = strtol(ptrWord, &checkPtr, 10);
            if (ptrWord == checkPtr) {
                ErrorExit();
            }

            ptrWord = checkPtr;
            element = strtod(ptrWord, &ptrWord);
            if (ptrWord == checkPtr) {
                ErrorExit();
            }

            set_elem(myMatrix, rowNumber, colNumber, element);
            if (strlen(ptrWord) != 0) {
                printf("Warning!: file contains extra characters: %s\nThe Matrix could be done wrong!\n\n", ptrWord);
            }
            fgetc(file);
            if ((i != numberOfNonZeroElements - 1) && (fscanf(file, "%[^\n]s", buffer) != 1)) {
                ErrorExit;
            }
        }

    } else {
        if (col == 1) {
            double firstElement;
            ptrWord = buffer;
            checkPtr = ptrWord;
            firstElement = strtod(ptrWord, &checkPtr);
            if (ptrWord == checkPtr) {
                ErrorExit();
            }

            if (row == 1) {
                fgetc(file);
                if (fscanf(file, "%[^\n]s", buffer) == EOF) {
                    set_elem(myMatrix, 0, 0, firstElement);
                    return myMatrix;
                }
            } else {
                fgetc(file);
                if (fscanf(file, "%[^\n]s", buffer) != 1) {
                    ErrorExit();
                }
            }

            double element;
            ptrWord = buffer;
            checkPtr = ptrWord;
            element = strtod(ptrWord, &checkPtr);
            if (ptrWord == checkPtr) {
                ErrorExit();
            }

            if (strlen(checkPtr) == 0) {
                set_elem(myMatrix, 0, 0, firstElement);
                set_elem(myMatrix, 1, 0, element);
                fgetc(file);
                if (fscanf(file, "%[^\n]s", buffer) != 1 && element != 1) {
                    ErrorExit();
                }
                ptrWord = buffer;
                checkPtr = ptrWord;
                for (int rowNumber = 2; rowNumber < row; rowNumber++) {
                    if (ptrWord == NULL) {
                        ErrorExit();
                    }
                    double element;
                    element = strtod(ptrWord, &ptrWord);
                    if (ptrWord == checkPtr) {
                        ErrorExit();
                    } else {
                        checkPtr = ptrWord;
                    }
                    set_elem(myMatrix, rowNumber, 0, element);

                    if (strlen(ptrWord) != 0) {
                        printf("Warning!: file contains extra characters: %s\nThe Matrix could be done wrong!\n\n",
                               ptrWord);
                    }
                    fgetc(file);
                    if ((rowNumber != row - 1) && (fscanf(file, "%[^\n]s", buffer) != 1)) {
                        free_matrix(myMatrix);
                        ErrorExit();
                    }
                    ptrWord = buffer;
                    checkPtr = ptrWord;
                }
            } else {
                numberOfNonZeroElements = (int) firstElement;

                for (int i = 0; i < numberOfNonZeroElements; i++) {
                    int rowNumber;
                    int colNumber;
                    if (i > 0) {
                        ptrWord = buffer;
                        checkPtr = ptrWord;
                        if (fscanf(file, "%[^\n]s", buffer) != 1) {
                            free_matrix(myMatrix);
                            ErrorExit();
                        }
                        rowNumber = strtol(ptrWord, &checkPtr, 10);
                        if (ptrWord == checkPtr) {
                            free_matrix(myMatrix);
                            ErrorExit();
                        }
                    } else {
                        rowNumber = (int) element;
                    }

                    ptrWord = checkPtr;
                    colNumber = strtol(ptrWord, &checkPtr, 10);
                    if (ptrWord == checkPtr) {
                        free_matrix(myMatrix);
                        ErrorExit();
                    }

                    ptrWord = checkPtr;
                    element = strtod(ptrWord, &ptrWord);
                    if (ptrWord == checkPtr) {
                        free_matrix(myMatrix);
                        ErrorExit();
                    }

                    set_elem(myMatrix, rowNumber, colNumber, element);
                    if (strlen(ptrWord) != 0) {
                        printf("Warning!: file contains extra characters: %s\nThe Matrix could be done wrong!\n\n",
                               ptrWord);
                    }
                    fgetc(file);
                }
            }

        } else {
            ptrWord = buffer;
            checkPtr = ptrWord;
            for (int rowNumber = 0; rowNumber < row; rowNumber++) {
                for (int colNumber = 0; colNumber < col; colNumber++) {
                    if (ptrWord == NULL) {
                        free_matrix(myMatrix);
                        ErrorExit();
                    }
                    double element;
                    element = strtod(ptrWord, &ptrWord);
                    if (ptrWord == checkPtr) {
                        free_matrix(myMatrix);
                        ErrorExit();
                    } else {
                        checkPtr = ptrWord;
                    }
                    set_elem(myMatrix, rowNumber, colNumber, element);
                }
                if (strlen(ptrWord) != 0) {
                    printf("Warning!: file contains extra characters: %s\nThe Matrix could be done wrong!\n\n",
                           ptrWord);
                }
                fgetc(file);
                if ((rowNumber != row - 1) && (fscanf(file, "%[^\n]s", buffer) != 1)) {
                    free_matrix(myMatrix);
                    ErrorExit();
                }
                ptrWord = buffer;
                checkPtr = ptrWord;
            }
        }

    }
    if (fscanf(file, "%[^\n]s", buffer) != EOF) {
        printf("Warning!: After the matrix are stored more characters\nhe Matrix could be done wrong!\n\n");
    }
    return myMatrix;
}


Matrix *create_matrix(int row, int col) {
    if (row < 1 || col < 1) {
        printf("Error! Incorrectly entered indexes elements\n");
        exit(EXIT_FAILURE);
    }
    Matrix *myMatrix = malloc(sizeof(myMatrix));
    if (myMatrix == NULL) {
        printf("Error! Memory is not allocated");
        exit(EXIT_FAILURE);
    }
    myMatrix->matrix = malloc(sizeof(double *) * row);

    if (myMatrix->matrix == NULL) {
        free(myMatrix);
        printf("Error! Memory is not allocated");
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < row; i++) {
        myMatrix->matrix[i] = calloc(col, sizeof(double));
        if (myMatrix->matrix[i] == NULL) {
            free(myMatrix);
            free(myMatrix->matrix);
            for (unsigned int j = 0; j < i; i++) {
                free(myMatrix->matrix[j]);
            }
            printf("Error! Memory is not allocated");
            exit(EXIT_FAILURE);
        }
    }
    myMatrix->cols = col;
    myMatrix->rows = row;
    return myMatrix;
}


void free_matrix(Matrix *matrix) {
    for (int i = 0; i < get_rows(matrix); i++) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix);
}


double get_elem(Matrix *matrix, int row, int col) {
    if ((row >= matrix->rows) || (col >= matrix->cols) || (row < 0) || (col < 0)) {
        printf("Error! Incorrectly entered indexes elements\n");
        free_matrix(matrix);
        exit(EXIT_FAILURE);
    }
    return matrix->matrix[row][col];
}

void set_elem(Matrix *matrix, int row, int col, double val) {
    if ((row >= matrix->rows) || (col >= matrix->cols) || (row < 0) || (col < 0)) {
        printf("Error! Incorrectly entered indexes elements\n");
        free_matrix(matrix);
        exit(EXIT_FAILURE);
    }
    matrix->matrix[row][col] = val;
}

int get_rows(Matrix *matrix) {
    return matrix->rows;
}


int get_cols(Matrix *matrix) {
    return matrix->cols;
}