#include "matrix.h"

//TODO
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX_SIZE_STRING 332

int the_number_in_the_string(char** string, char* error);
double double_number_transformer(char** string);
int not_rarefied_matrix_filling(Matrix* matrix, char* string, int row_position);
int rarefied_matrix_filling(Matrix* matrix, char* string);


Matrix* create_matrix_from_file(FILE* file) {

	if (file == NULL) {
		printf("Не могу открыть файл\n");
		_Exit(-1);
	}
	int row = 0;
	int col = 0;
	int number_of_nonzero_elements = 0;
	int mod = 0;
	char* string = calloc((size_t)MAX_SIZE_STRING, sizeof(char));
	Matrix* matrix = 0;
	for (int i = 0; fgets(string, MAX_SIZE_STRING, file) != NULL; i++) {
		int string_size = strlen(string) - 1;
		if (*(string + string_size) != '\n' && *(string + string_size + 1) != '\0') {
			printf("Ошибка, строка файла слишком длинная\n");
			fclose(file);
			_Exit(-1);
		}
		if (i == 0) {
			if ((row = the_number_in_the_string(&string, "Некоректное число строк\n")) == -1) {
				 fclose(file);
				_Exit(-1);
			}
			continue;
		}
		if (i == 1) {
			if ((col = the_number_in_the_string(&string, "Некоректное число столбцов\n")) == -1) {
				fclose(file);
                                _Exit(-1);
			}
			continue;
		}
		if (i == 2) {
			matrix = create_matrix(row, col);
			if ((strstr(string, " ")) == NULL) {
				mod = 2;
				if ((number_of_nonzero_elements = the_number_in_the_string(&string, "Некоректное число ненулевых элементов\n")) == -1) {
					fclose(file);
	                                _Exit(-1);
				}
				continue;
			}
			else
				mod = 1;
		}
		if (mod == 1) {
			int row_position = i - 2;
			if (not_rarefied_matrix_filling(matrix, string, row_position) == -1) {
				fclose(file);
                                _Exit(-1);
			}
		}
		if (mod == 2) {
			if (i == number_of_nonzero_elements + 3) {
				fclose(file);
                                _Exit(-1);
			}
			if (rarefied_matrix_filling(matrix, string) == -1) {
				fclose(file);
                                _Exit(-1);
			}
		}
	}
	return matrix;
}

Matrix* create_matrix(int row, int col) {
	Matrix* matrix = malloc(sizeof(Matrix));
	matrix->row = row;
	matrix->col = col;
	matrix->value = (double**)malloc(row*sizeof(double*));
	for (int i = 0; i < row; i++) {
		matrix->value[i] = (double*)malloc(col*sizeof(double));
		for (int j = 0; j < col; j++) {
			matrix->value[i][j] = 0;
		}
	}
	return matrix;
}

void free_matrix(Matrix* matrix) {
	free((*matrix).value);
	free(matrix);
}

double get_elem(Matrix* matrix, int row, int col) {
	return (*(*((*matrix).value + row) + col));
}

void set_elem(Matrix* matrix, int row, int col, double val) {
	(*(*((*matrix).value + row) + col)) = val;
}

int get_rows(Matrix* matrix) {
	return matrix->row;
}

int get_cols(Matrix* matrix) {
	return matrix->col;
}

int the_number_in_the_string(char** string, char* error) {
	
	int string_size = strlen(*string) - 1;
	int number = 0;
	while (*(*string) != '\n' && *(*string) != ' ') {
		if (isdigit(*(*string)) == 0) {
			printf("%s\n", error);
			return -1;
		}
		else
			number = number * 10 + (**string - '0');
		(*string)++;
	}
	return number;
}

int not_rarefied_matrix_filling(Matrix* matrix, char* string, int row_position) {
	for (int i = 0; i < (*matrix).col; i++) {
		if (*(string) == ' ') {
			string++;
		}
		if (*(string) == '\n')
			return -1;
		else {
			*(*((*matrix).value + row_position) + i) = (double)double_number_transformer(&string);
		}
	}
}

int rarefied_matrix_filling(Matrix* matrix, char* string) {
	int row_number = 0;
	int col_number = 0;
	double value = 0;
	if ((row_number = the_number_in_the_string(&string, "Некорректный номер строки\n")) == -1)
		return -1;
	string++;
	if ((col_number = the_number_in_the_string(&string, "Некорректный номер столбца\n")) == -1)
		return -1;
	string++;
	if ((*(*((*matrix).value + row_number) + col_number) = (double)double_number_transformer(&string)) == -1)
		return -1;
	string++;

}

double double_number_transformer(char** string) {
	double number = 0;
	int after_point_mod = 0;
	int the_number_of_numbers_after_point = 0;
	while (*(*string) != ' ' && *(*string) != '\n' && *(*string) != '\0') {
		if ((isdigit(*string == 0)) && (((**string == '.') || (**string == ',')) && (after_point_mod == 1))) {
			printf("Неккоректный элемент матрицы\n");
			return -1;
		}
		else if ((**string == '.') || (**string == ','))
			after_point_mod = 1;
		else {
			number = number * 10 + (double)(**string - '0');
			if (after_point_mod == 1)
				the_number_of_numbers_after_point++;
		}
		(*string)++;
	}

	while (the_number_of_numbers_after_point > 0) {
		number /= 10;
		the_number_of_numbers_after_point--;
	}
	return number;
}
