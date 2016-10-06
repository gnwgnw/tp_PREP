#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "generate_matrix.h"

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Need more arguments!\n");
        abort();
    }

   // if (strcmp(argv[2], "g") == 0) {	
       // generate_matrix_to_file(5,5,10);	
   // }										

    const char *filePath = argv[1];
    
    FILE *file = NULL;
    if ((file = fopen(filePath, "r")) == 0) {
        fprintf(stderr, "File not exists!\n");
        abort(); 
    }

    Matrix* mat = create_matrix_from_file(file);
    Matrix* t_mat;
    printf("Normal matrix:\n");
    print_matrix(mat);
    t_mat = transpose(mat);
    printf("Transposed matrix:\n");
    print_matrix(t_mat);
    printf("max-norm = %.3lf\nl-norm = %.3lf\ne-norm = %.3lf\n",
                    max_norm(mat), l_norm(mat), e_norm(mat));
    free_matrix(t_mat);
    free_matrix(mat);
    return 0;

}
