
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

double find_max_norma(Matrix *matr)
{
    double sum = 0;
    double max_sum = get_elem(matr, 0, 0);
    for (int i = 0; i < get_rows(matr); i++)
    {
        for (int j = 0; j < get_cols(matr); j++)
            sum += get_elem(matr, i, j);
        if (sum > max_sum) max_sum = sum;
        sum = 0;
    }
    return max_sum;
}

int main(int argc, char* argv[])
{
    //TODO
    FILE *file;
    if(argc < 2)
    {
        printf("Недостаточно парамеров\n");
        return 0;
    }
    for (int i = 1; i < argc; i++)
    {
        file = fopen(argv[i], "rt");
        if (file == NULL)
        {
            printf("Невозможно открыть файл '%s'\n", argv[i]);
            continue;
        }
        Matrix *matr = create_matrix_from_file(file);
        if (matr == NULL)
        {
            printf("Ошибка при создании матрицы '%s'\n", argv[i]);
            fclose(file);
            continue;
        }
        fclose(file);
        printf("\nМаксимальная норма для матрицы '%s' %lf\n", argv[i], find_max_norma(matr));
        free_matrix(matr);
    }
    return 0;
}
