#include<stdio.h>
#include<stdlib.h>
#include"matrix.h"
#include"matrix_add.h"

int main(int argc, char* argv[])
{

    if(argc != 3)
    {
        printf("2 args required: one per matrix!\n");
        return -1;
    }

    FILE *f1 = fopen(argv[1], "r");
    if(f1 == NULL)
    {
        printf("Can't open file %s\n", argv[1]);
        return -1;
    }

    FILE *f2 = fopen(argv[2], "r");
    if(f2 == NULL)
    {
        printf("Can't open file %s\n", argv[2]);
        fclose(f2);
        return -1;
    }


    Matrix *mtrx1 = create_matrix_from_file(f1);
    if(mtrx1 == NULL)
    {
        printf("Can't allocate memory!\n");
        fclose(f1);
        fclose(f2);

        return -2;
    }

    Matrix *mtrx2 = create_matrix_from_file(f2);
    if(mtrx2 == NULL)
    {
        printf("Can't allocate memory!\n");
        fclose(f1);
        fclose(f2);

        return -2;
    }

    printf("First matrix: \n");
    print_matrix(stdout, mtrx1);
    printf("----------\n");
    printf("Second matrix: \n");
    print_matrix(stdout, mtrx2);
    printf("----------\n");

    int errcode = 0;
    Matrix *res = mult_matrix(mtrx1, mtrx2, &errcode);

    if(errcode == -1)
        printf("Matrixes are empty!\n");
    else if(errcode == -2)
        printf("Matrixes are not compatable!\n");
    else
    {
        printf("Result of multiplication: \n");
        print_matrix(stdout, res);
        printf("----------\n");
    }

    free_matrix(mtrx1);
    free_matrix(mtrx2);
    if(res != NULL)
        free_matrix(res);

    fclose(f1);
    fclose(f2);

    return 0;
}
