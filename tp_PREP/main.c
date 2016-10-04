#include <stdio.h>
#include <process.h>
#include "matrix.h"

int main(int argc, char* argv[])
{
    FILE * f = NULL;
    if ( ( f = fopen(argv[1], "r") ) == NULL ){
        perror("fopen");
        exit(1);
    }

    Matrix *my_matrix =  create_matrix_from_file(f);
    free_matrix(my_matrix);

    if ( fclose(f) )
        perror("fclose");
    return 0;
}