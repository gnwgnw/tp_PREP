#include "matrix.h"
#include <stdlib.h>
#include <ctype.h>

void output_matrix(Matrix* matrix);
Matrix* transposition(Matrix* matrix);

int main(int argc, char* argv[])
{
	FILE *fp;
	Matrix *matrix = NULL;
	Matrix *new_matrix = NULL;

	if(argc < 2){
		printf("Error\n");
		exit (1);
	}

  	if ((fp = fopen(argv[1], "r")) == NULL){
		printf("Open failed: %s\n", argv[1]);
		exit (1);
		}
	
	matrix = create_matrix_from_file(fp);
	new_matrix = transposition(matrix);

	output_matrix(matrix);
	putchar('\n');
	output_matrix(new_matrix);

	fclose(fp);
	free_matrix(matrix);
	free_matrix(new_matrix);
	return 0;
}

void output_matrix(Matrix* matrix){
	int i, j;
	int row = get_rows(matrix);
	int col = get_cols(matrix);

	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++)
			printf("%12lf " , get_elem(matrix, i, j));
		printf("\n");
	}
}

Matrix* transposition(Matrix* matrix){
	Matrix* new_matrix = NULL;
	int i, j;
	double val = 0.0;
	int row = get_rows(matrix);
	int col = get_cols(matrix);

	new_matrix = create_matrix(col, row);

	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++){
			val = get_elem(matrix, i, j);
			set_elem(new_matrix, j, i, val);
		}

	return new_matrix;
}
