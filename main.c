#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "generate_matrix.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Need more arguments!\n");
        abort();
    }

    FILE *fileInput = NULL;
    if (argv[argc-1] == "gen") {
        generate_matrix_to_file(10,10,100);
    }
    if ((fileInput = fopen(argv[1], "r")) == 0) {
        printf("File not exists!\n");
        return 1;
    }
    Matrix* man = create_matrix_from_file(fileInput);
    print_matrix(man);
    printf("max-norm = %.3lf\nl-norm = %.3lf\ne-norm = %.3lf\n",
                    max_norm(man), l_norm(man), e_norm(man));
    man = transpose(man);
    print_matrix(man);
    free_matrix(man);
    return 0;
}

