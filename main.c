#include "matrix.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        puts("invalid args");
        return 1;
    }

    FILE* pFile = fopen(argv[1], "r");

    if (pFile == NULL)
    {
        puts("cannot open file");
        return 2;
    }
    
    Matrix* matrix = create_matrix_from_file(pFile);
    
    Matrix* transp = create_matrix(matrix->cols, matrix->rows);
    
    double val = 0.0;
    int i, j;
    for (i = 0; i < transp->rows; i++)
    {
        for (j = 0; j < transp->cols; j++)
        {
            val = get_elem(matrix, j, i);
            set_elem(transp, i, j, val);
        }
    }
    
    for (i = 0; i < matrix->rows; i++)
    {
        for (j = 0; j < matrix->cols; j++)
        {
            printf("%lf \t", get_elem(matrix, i, j));
        }
        putchar('\n');
    }
    putchar('\n');
        
    for (i = 0; i < transp->rows; i++)
    {
        for (j = 0; j < transp->cols; j++)
        {
            printf("%lf \t", get_elem(transp, i, j));
        }
        putchar('\n');
    }
    
    free_matrix(matrix);
    free_matrix(transp);
    
    return 0;
}
