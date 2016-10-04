#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void mul_matrix(Matrix *matr1, Matrix *matr2, int m, int q, int n);

int main(int argc, char* argv[])
{

    if (argc != 3) {
        printf("Wrong arguments!\nProgram aborted!\n");
        return 0;
    }

    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");

    if (file1 == NULL || file2 == NULL)
    {
        printf("Cannot open file(s)!\nProgram aborted!\n");
        return 0;
    }

    Matrix *matr1 = create_matrix_from_file(file1);
    Matrix *matr2 = create_matrix_from_file(file2);
    fclose(file1);
    fclose(file2);

    if (matr1 == NULL || matr2 == NULL)
    {
        printf("Matrix creating error!\nProgram aborted!\n");
        return 0;
    }

    int row_num1 = 1, col_num1 = 1;
    int row_num2 = 1, col_num2 = 1;

    row_num1 = get_rows(matr1);
    col_num1 = get_cols(matr1);
    row_num2 = get_rows(matr2);
    col_num2 = get_cols(matr2);

    if (col_num1 != row_num2)
    {
        printf("Matrix sizes do not match!\nProgram aborted!\n");
        return 0;
    }
    int row_num3 = row_num1;
    int col_num3 = col_num2;

    mul_matrix(matr1, matr2, row_num3, col_num3, col_num1);

    free_matrix(matr1);
    free_matrix(matr2);

    return 0;
}

void mul_matrix(Matrix *matr1, Matrix *matr2, int m, int q, int n)
{
    int i = 0, j = 0, r = 0;
    double cur_elem;

    printf("\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < q; j++)
        {
            cur_elem = 0.0;
            for (r = 0; r < n; r++)
            {
                cur_elem += get_elem(matr1, i, r) * get_elem(matr2, r, j);
            }
            printf("%6.2f ", cur_elem);
        }
        printf("\n");
    }
    printf("\n");
}
