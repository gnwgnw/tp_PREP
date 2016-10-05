#include "matrix.h"

int main (int argc, char *argv[])
{
    if (argc <= 2){
        printf("You enter a few files.\n");
        return 1;}

    FILE* matrix_file = NULL;

    matrix_file = fopen(argv[1], "r");

    if (!matrix_file) {
        printf("Error: Cannot open %s\n", argv[1]);
        return 1;
    }

    Matrix* A = create_matrix_from_file(matrix_file);
    fclose(matrix_file);
    
    if (!A)
        return 1;

    matrix_file = fopen(argv[2], "r");
    Matrix* B = create_matrix_from_file(matrix_file);

    if (!matrix_file) {
        printf("Error: Cannot open %s\n", argv[2]);
        free_matrix(A);
        return 1;
    }

    fclose(matrix_file);

    if (!B) {
        free_matrix(A);
        return 1;
    }

    Matrix* C = multiply(A, B);
    free_matrix(A);
    free_matrix(B);
    
    int check = 0;    
    if (argc > 3){
	int k = 3;
        for (; k < argc; ++k){
            matrix_file = fopen(argv[k], "r");
            
            if (!matrix_file) {
                printf("Error: Cannot open %s\n", argv[k]);
                check = 1;
                break;
            }

            Matrix* D = create_matrix_from_file(matrix_file);
            fclose(matrix_file);

            if (!D) {
                check = 1;
                break;
            }

            Matrix* TMP = multiply(C, D);
            free_matrix(D);

            if (!TMP) {
                check = 1;
                break;
            }

	    copy_matrix(C, TMP);
	    free_matrix(TMP);
        }
    }
    if (!check && C)
        display(C);
    free_matrix(C);
    return 0;
}
