#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include "matrix.h"

// Евгения Невтриносова 
void Refund(char *numWord, int *nRow, int *nCol, double *number, int realRow, int realCol, bool *go_to) {
    char *ptr = NULL;
    char *control = numWord;
    char *fWord = malloc(sizeof(*fWord) * 64);

    if (((*nRow = strtol(numWord, &ptr, 10)) < 0) || ((*nRow = strtol(numWord, &ptr, 10)) > realRow)) {
        printf("Error! Wrong meaning!\n");
        *go_to = false;
    }

    if ((control == ptr) && (*go_to)) {
        printf("Error! Wrong meaning!!!\n");
        *go_to = false;
    }

    numWord = ptr;
    control = ptr;

    if ((((*nCol = strtol(numWord, &ptr, 10)) < 0) || ((*nCol = strtol(numWord, &ptr, 10)) > realCol)) && (*go_to)) {
        printf("Error! Wrong meaning!\n");
        *go_to = false;
    }

    if ((control == ptr) && (*go_to)) {
        printf("Error! Wrong meaning!!!\n");
        *go_to = false;
    }

    numWord = ptr;
    control = ptr;

    *number = strtod(numWord, &ptr);

    if ((control == ptr) && (*go_to)) {
        printf("Error! Wrong meaning!!!\n");
        *go_to = false;
    }


    if ((strlen(ptr) != 0) && (*(ptr + 1) ) && (*go_to)) {
        printf("Error! Wrong meaning!!!\n");
        *go_to = false;
    }

    free(fWord);

}


void secondRefund(char *numWord, int Row, int Col, bool *go_to, Matrix *myMatrix) {
    char *ptr = NULL;
    char *control = numWord;
    double number[Col];

    for (int i = 0; i < Col; ++i) {
        if (go_to) {
            number[i] = strtod(numWord, &ptr);

            if (control == ptr) {
                printf("Error! Wrong meaning!!!\n");
                *go_to = false;
            }

            numWord = ptr;
            control = ptr;
        }
    }


    if (((strlen(ptr) != 0) && (*(ptr + 1))) && (go_to)) {
        printf("Error! Wrong meaning!\n");
        *go_to = false;
    }

    if (go_to) {
        for (int j = 0; j < Col; ++j) {
            set_elem(myMatrix, Row, j, number[j]);
        }
    }
}

Matrix *create_matrix_from_file(FILE *matrixFile) {
    char *numWord = malloc(sizeof(*numWord) * 64);
    char *ptr;
    int num = 1000;
    int Col = 0;
    int Row = 0;
    double notNull = 0;
    bool go_to = true;

    fgets(numWord, num, matrixFile);
    Row = strtol(numWord, &ptr, 10);
    ptr++;
    if (*ptr) {
        printf("Error! Excess symbols in the line!\n");
        go_to = false;
    }

    if (Row < 0) {
        printf("Error! Negative number of rows\n");
        go_to = false;
    }

    numWord[0] = '\0';
    ptr = NULL;

    fgets(numWord, num, matrixFile);
    if (go_to) {
        Col = strtol(numWord, &ptr, 10);
        ptr++;
        if (*ptr) {
            printf("Error! Excess symbols in the line!\n");
            go_to = false;
        }
        numWord[0] = '\0';
        if (Col < 0) {
            printf("Error! Negative number of columns\n");
            go_to = false;
        }
    }

    struct Matrix *myMatrix = create_matrix(Row, Col);

    ptr = NULL;
    bool process1 = true;
    bool process2 = true;
    int nextRow = 0;


    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            myMatrix->Matr[i][j] = 0;
        }
    }

    fgets(numWord, num, matrixFile);
    if (go_to) {
        notNull = strtod(numWord, &ptr);
        ptr++;
        if (*ptr) {

            secondRefund(numWord, 0, Col, &go_to, myMatrix);
            process1 = false;
            for (int i = 1; i < Row; ++i) {
                if ((fgets(numWord, num, matrixFile) != NULL) && (go_to)) {
                    secondRefund(numWord, i, Col, &go_to, myMatrix);

                } else {
                    printf("Error! The end of file!Create correctly matrix!\n");
                    go_to = false;
                    break;
                }

            }
            if (fgets(numWord, num, matrixFile) != NULL) {
                printf("Error! Enter too much rows!\n");
                go_to = false;
            }

        } else {
            process2 = false;
            numWord[0] = '\0';

            fgets(numWord, num, matrixFile);
            nextRow = strtod(numWord, &ptr);

            if (!((strlen(ptr) != 0) && (*(ptr + 1)))) {
                process2 = true;
                process1 = false;
                set_elem(myMatrix, 0, 0, notNull);
                set_elem(myMatrix, 1, 0, nextRow);

                for (int k = 2; k < Row; ++k) {
                    if ((fgets(numWord, num, matrixFile) != NULL) && (go_to)) {
                        secondRefund(numWord, k, Col, &go_to, myMatrix);

                    } else {
                        printf("Error! The end of file!Create correctly matrix!\n");
                        go_to = false;
                        break;
                    }

                }

            } else {
                int nRow = 0;
                int nCol = 0;
                double number = 0;
                process1 = true;
                process2 = false;
                myMatrix->row = Row;
                myMatrix->col = Col;
                myMatrix->notNull = notNull;

                Refund(numWord, &nRow, &nCol, &number, Row, Col, &go_to);
                set_elem(myMatrix, nRow, nCol, number);

                if ((Row != 0) && (Col != 0) && (notNull != 0) && (go_to) && (process1)) {
                    for (int n = 1; n < myMatrix->notNull; n++) {
                        if ((fgets(numWord, num, matrixFile) != NULL) && (go_to)) {
                            nCol = 0;
                            nRow = 0;
                            number = 0;
                            Refund(numWord, &nRow, &nCol, &number, Row, Col, &go_to);
                            if (go_to) {
                                set_elem(myMatrix, nRow, nCol, number);
                                numWord[0] = '\0';
                            }
                        } else {
                            printf("Error! The end of file!Create correctly matrix!\n");
                            go_to = false;
                            break;
                        }
                    }
                    if (fgets(numWord, num, matrixFile) != NULL){
                        printf("Error! The end of file!Create correctly matrix!\n");
                        go_to = false;
                    }


                } else {
                    if (process1) {
                        printf("Error! Number of columns or rows or nonzero elements = 0 or not introduced or negative!\n");
                        myMatrix->row = 0;
                        myMatrix->col = 0;
                        myMatrix->notNull = 0;
                        free_matrix(myMatrix);
                        myMatrix = create_matrix(0, 0);
                    }
                }

                process1 = false;
                process2 = false;
            }

            if (notNull < 0) {
                printf("Error! Negative number of nonzero elements\n");
                go_to = false;
            }
        }
    }

    free(numWord);
    return myMatrix;
}


Matrix *create_matrix(int row, int col) {
    Matrix *myMatrix = malloc(sizeof(myMatrix));
    myMatrix->Matr = malloc(sizeof(double *) * row);
    for (int i = 0; i < row; i++) {
        myMatrix->Matr[i] = malloc(sizeof(double) * col);
    }
    myMatrix->col = col;
    myMatrix->row = row;
    return myMatrix;
}

double get_elem(Matrix *matrix, int row, int col) {
    if ((row > matrix->row) || (col > matrix->col) || (col < 0) || (row < 0)) {
        printf("Error! Wrong value of row or column.");
        return -1;
    }
    return matrix->Matr[row][col];
}

void set_elem(Matrix *matrix, int row, int col, double val) {
    matrix->Matr[row][col] = val;
}

int get_rows(Matrix *matrix) {
    return matrix->row;
}

int get_cols(Matrix *matrix) {
    return matrix->col;
}

void free_matrix(Matrix *matrix) {
    for (int i = 0; i < get_rows(matrix); i++) {
        free(matrix->Matr[i]);
    }
    free(matrix->Matr);
    free(matrix);
}
