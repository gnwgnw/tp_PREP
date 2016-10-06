#include "matrix.h"
#include <string.h>
#include <stdlib.h>
// Евгения Невтриносова

int main(int argc, char* argv[]) {
    if (argc!=2){
        printf("Error! Enter too much or too few values!\n");
        return 1;
    }

    FILE *matrixFile;
    if (((matrixFile = fopen(argv[1],"r"))==NULL)){
        printf("Error! File is not open!\n");
        return 0;
    }

    int num = 1000;
    char *numWord = malloc(sizeof(*numWord) *64);
    fgets(numWord, num, matrixFile);

    if (!(*(numWord+1))){
        printf("Error! File is empty or uncorrect!\n");
        return 0;
    }

    free(numWord);

    fclose(matrixFile);
    matrixFile = fopen(argv[1],"r");

    struct Matrix *myMatrix;
    myMatrix = create_matrix_from_file(matrixFile);

    double norma=0;
    double max=1.7e-308;
    for (int i=0; i<myMatrix->col; ++i){
        for (int j=0; j<myMatrix->row; ++j){
            norma += get_elem(myMatrix, j, i);
        }
        if (norma>max){
            max = norma;
        }
        norma = 0;
    }

    printf("Матрица :\n");
    for (int k=0; k<myMatrix->row; ++k){
        for(int m=0; m<myMatrix->col; ++m){
            printf("%.2f ", myMatrix->Matr[k][m]);
        }
        printf("\n");
    }

    if ((myMatrix->col!=0)&&(myMatrix->row!=0)) {
        printf("В матрице %d строк(-и) и %d столбца(-ов) \n", get_rows(myMatrix), get_cols(myMatrix));
        printf("Максимальная норма матрицы = %.3f\n", max);
    }

    fclose(matrixFile);
    free_matrix(myMatrix);


	return 0;
}
