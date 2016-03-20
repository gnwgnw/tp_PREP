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
    
    fclose(pFile);
    
    int matrixRows = get_rows(matrix);
    int matrixCols = get_cols(matrix);
    
    int transpCols = matrixRows;
    int transpRows = matrixCols;
    
    Matrix* transp = create_matrix(transpRows, transpCols);
    
    double val = 0.0;
    for (int i = 0; i < transpRows; i++)
    {
        for (int j = 0; j < transpCols; j++)
        {
            val = get_elem(matrix, j, i);
            set_elem(transp, i, j, val);
        }
    }
    
    
    for (int i = 0; i < matrixRows; i++)
    {
        for (int j = 0; j < matrixCols; j++)
        {
            printf("%lf \t", get_elem(matrix, i, j));
        }
        putchar('\n');
    }
    
    putchar('\n');
   
    for (int i = 0; i < transpRows; i++)
    {
        for (int j = 0; j < transpCols; j++)
        {
            printf("%lf \t", get_elem(transp, i, j));
        }
        putchar('\n');
    }
    
    free_matrix(matrix);
    free_matrix(transp);
    
    return 0;
}
