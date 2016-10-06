#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Wrong number of arguments");
    }
    else
    {
        //create_matrix_from_file(fopen(argv[1], "r"));
        Matrix *matrix = create_matrix_from_file(fopen(argv[1], "r"));
        free_matrix(matrix);
    }
    return 0;
}
