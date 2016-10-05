#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define ERROR_EXIT 1
#define SUCCESS_EXIT 0
#define MAX_LENGTH 255

Matrix* create_matrix_from_file(FILE* file) {
	
	if (!file) {
		printf("This file do not exist\n");
		exit(ERROR_EXIT);
	}	
	check_file(file);
	int rows_n;
	int cols_n;
	if (fscanf(file, "%d%d", &rows_n, &cols_n) != 2) exit(ERROR_EXIT);
	Matrix *matr = (Matrix *)malloc(sizeof(Matrix));
	matr->rows_N = rows_n;
	matr->cols_M = cols_n;
	matr->matrix = (double **)malloc(rows_n*sizeof(double *));
	for (int i = 0; i < rows_n; ++i) {
		matr->matrix[i] = (double *)malloc(cols_n*sizeof(double));
	}
	double val;
	for (int i = 0; i < rows_n; ++i) {
		for (int j = 0; j < cols_n; ++j) {
			if (fscanf(file, "%lf", &val) != 1) exit(ERROR_EXIT);
			matr->matrix[i][j] = val;
		}
	}
	printf("Matrix from input file:\n");
	print_matrix (matr);
	return matr;
}


Matrix* create_matrix(int row, int col) {
	
	Matrix *matr = (Matrix *)malloc(sizeof(Matrix));
	matr->rows_N = row;
	matr->cols_M = col;
	matr->matrix = (double **)malloc(row*sizeof(double *));
	for (int i = 0; i < row; ++i) {
		matr->matrix[i]=(double *)malloc(col*sizeof(double));
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			matr->matrix[i][j] = 0.00;
		}
	}
	return matr;
}

void free_matrix(Matrix* matrix) {
	for (int i = 0; i < matrix->rows_N; ++i) {
		free (matrix->matrix[i]);
	}
	free (matrix->matrix);
	free (matrix);
}


double get_elem(Matrix* matrix, int row, int col) {
	if (row >= matrix->rows_N || col >= matrix->cols_M || row < 0 || col < 0) {
		printf("Out of array\n");
		free_matrix(matrix);
		exit(ERROR_EXIT);
	}
	return matrix->matrix[row][col];
}


void set_elem(Matrix* matrix, int row, int col, double val) {
	if (row >= matrix->rows_N || col >= matrix->cols_M || row < 0 || col < 0) {
		printf("Out of array\n");
		free_matrix(matrix);
		exit(ERROR_EXIT);
	}
	matrix->matrix[row][col]=val;
}


int get_rows(Matrix* matrix) {
	return matrix->rows_N;
}

int get_cols(Matrix* matrix) {
	return matrix->cols_M;
}

void print_matrix(Matrix* matrix) {	 
	printf("\n");
	for (int i = 0; i < matrix->rows_N; ++i) {
		for (int j = 0; j < matrix->cols_M; ++j) {
			printf("%10.2lf", matrix->matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void check_file(FILE* file) {
	char str[MAX_LENGTH];
	for (int j = 0; j < 2; ++j) {
		if (fgets(str, sizeof(str), file) == 0) {
			printf("File consist 2 or less line\n");
			exit(ERROR_EXIT);
		}
		if (strlen(str) == MAX_LENGTH-1) {
			printf("Exceeded max length\n");
			exit(ERROR_EXIT);
		}
		for (unsigned int i = 0; i < strlen(str); ++i) {
			if (isspace(str[i])) {
				if (i != (strlen(str)-1)) {
					printf("Incorrect format\n"); 
					exit(ERROR_EXIT);
				}
				else continue;
			}

			if (isdigit(str[i]) == 0) {
				printf("The first two lines must contain only integers\n");
				exit(ERROR_EXIT);
			}
		}
	}
	rewind (file);

	int row;
	int col;
	int spc;
	int space;
	int pct;

	if (fscanf(file,"%d%d%*c", &row, &col) != 2) exit(ERROR_EXIT);
	for (int i = 0; i < row; ++i) {
		if (fgets (str, sizeof(str), file) == 0) {
			printf("Not enough lines\n");
			exit(ERROR_EXIT);
		}
		if (strlen(str) == MAX_LENGTH-1) {
			printf("Exceeded max length\n");
			exit(ERROR_EXIT);
		}
		space = 0;
		spc = pct = 0;
		for (unsigned int j = 0; j < strlen(str); ++j) {
			
			if (isalpha(str[j])) {
				printf("Letters in the matrix\n");
				exit(ERROR_EXIT);
			}
			
			if (ispunct(str[j])) {
				spc = 0;
				pct = 1;
				continue;
			}
			
			if (isdigit(str[j])) {
				pct = 0;
				spc = 0;
				continue;
			}

			if (isspace(str[j])) {
				++space;
				if (pct == 1 || spc == 1 || j == 0) {
					printf("Incorrect format of file\n");
					exit(ERROR_EXIT);
				}
				pct = 0;
				spc = 1;
			}
		}
		if (space != col) {
			printf("Wrong number of columns\n");
			exit(ERROR_EXIT);
		}
	}
	if (fgetc(file) != EOF) {
		printf("Too many rows\n");
		exit(ERROR_EXIT);
	}
	rewind(file);

	if (fscanf(file,"%d%d", &row, &col) != 2) exit(ERROR_EXIT);
	float t;
	for (int i = 0; i < (row*col); ++i) {
		if (fscanf(file, "%f ", &t) == 0) {
			printf("Element (%d,%d) is incorrect\n", (i/col), (i%col));
			exit(ERROR_EXIT);
		} 
	}
	if (!feof(file)) {
		printf("One of the matrix's elemets is incorrect\n");
		exit(ERROR_EXIT);
	}
	rewind(file);
}
