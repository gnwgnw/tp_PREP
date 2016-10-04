#include "matrix.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

static double euclidean_norm(Matrix *matrix){
    assert(matrix && "NULL pointer");

    double summ_square_of_elem = 0;
    double eucl_norm = 0;

    for(int i = 0; i < get_rows(matrix); ++i){
        for(int j = 0; j < get_cols(matrix); ++j){
            summ_square_of_elem += pow(get_elem(matrix, i, j), 2);
        }
    }

    eucl_norm = sqrt(summ_square_of_elem);

    return eucl_norm;
}

int main(int argc, char* argv[])
{

    if(argc == 1){
        printf("BAD INOUT ARGUMENTS");
        return -1;
    }
    for(int i = 1; i< argc; ++i){
        FILE *matrix_file = fopen(argv[i], "rb");
        if(!matrix_file){
            printf("bad open input file %s\n", argv[i]);
            fclose(matrix_file);
            continue;
        }

        Matrix *matrix = create_matrix_from_file(matrix_file);
        if(!matrix){
            printf("Bad create matrix from file %s\n", argv[i]);
            free_matrix(matrix);
            fclose(matrix_file);
            continue;
        }

        double ec_norm = euclidean_norm(matrix);
        printf("number file = %d;   euclidean_norm = %f\n", i, ec_norm);

        free_matrix(matrix);
        fclose(matrix_file);
    }



//    FILE *matrix_file = fopen("/home/anton/_programming/mail/course/c_plus_plus/dz2/project/input_matrix/square_matrix.txt", "rb");
//    if(!matrix_file){
//        printf("bad open input file\n");
//        return -1;
//    }

//    Matrix *matrix = create_matrix_from_file(matrix_file);
//    if(!matrix){
//        printf("Bad create matrix form file\n");
//        return -1;
//    }

//    Matrix *m1 = create_matrix(4,4);

//    int r_m1 = get_rows(m1);
//    int r_matrix = get_rows(matrix);
//    printf("\nr_matrix = %d\nr_m1 = %d\n", r_matrix, r_m1);

//    double ec_norm = euclidean_norm(matrix);
//    printf("ec_norm = %f\n", ec_norm);
//    ec_norm = euclidean_norm(m1);
//    printf("ec_norm = %f\n", ec_norm);


//    free_matrix(matrix);
//    free_matrix(m1);
//    fclose(matrix_file);



    return 0;
}
