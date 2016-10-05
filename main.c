#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char* argv[])
{    
    if (argc != 2)
     {
        printf("Incorrect number of arguments");
        exit(EXIT_FAILURE);
      }
    
    FILE *matrix_file = fopen(argv[1],"r+t");
        if (matrix_file == NULL) 
      {
      perror("Can't open file");
      exit(EXIT_FAILURE);
      }

    Matrix *matrix = create_matrix_from_file(matrix_file);

    fclose(matrix_file);

    int rows = get_rows(matrix);
    int cols = get_cols(matrix);
    
    double l_norm[cols];
    for (int j = 0; j < cols; ++j)
    {
      double sum_in_col = 0;
      for (int i = 0; i < rows; ++i)
        {
         sum_in_col+=fabs(matrix->elem[i][j]); 
        }
      l_norm[j] = sum_in_col; 
    }

    double max_norm = l_norm[0];
    for (int i = 0; i < rows; ++i)
      {
        if (l_norm[i] > max_norm)
          max_norm = l_norm[i]; 
      }

    printf("\nMax norm is %.2f\n", max_norm);

    free_matrix(matrix);

    return 0;
}
