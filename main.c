#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define ERROR_EXIT 1
#define SUCCESS_EXIT 0

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Enter single file\n");
		exit(ERROR_EXIT);
	}
	FILE* in = fopen(argv[1], "r");
	if (!in) {
		printf("File '%s' do not exist\n", argv[1]);
		exit(ERROR_EXIT);
	}
	Matrix *ptr_matr1 = create_matrix_from_file(in);
	int row = get_rows(ptr_matr1);
	int col = get_cols(ptr_matr1);
	double B[row];
	double Max = 0.00;
	for (int i = 0; i < row; ++i) {
		B[i] = 0.00;
		for (int j = 0; j < col; ++j) {
			B[i] = B[i] + fabs(get_elem(ptr_matr1, i, j));
		}
		if (B[i] > Max) Max = B[i];
	}
	printf ("\nMax matrix norm: %.2lf\n\n", Max);
	free_matrix(ptr_matr1);
	fclose(in);
	return SUCCESS_EXIT;
}
