#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "matrix.h"

#define NO_NAME -1
#define CANT_READ -2
#define ERROR -1

Matrix *matrix;

int comparator(const void*, const void*);
int swap(Matrix *, int);
void transpon(Matrix *);
void print_matrix(const int, const int, const Matrix *);
int *consider_struct_element(const Matrix *);

int main(int argc, char *argv[])
{
	FILE *fp;
	//обработка ошибок
	if (argc < 2) {
		printf("нет имени файла с матрцицей\n");
		return NO_NAME;
	}
	if ((fp = fopen(argv[1], "r")) == NULL) {
			printf("не могу прочесть файл %s\n", argv[1]);
			return CANT_READ;
		}

	fp = fopen(argv[1], "r");
	matrix = create_matrix_from_file(fp);
	if (matrix == NULL)
		return ERROR;
	fclose(fp);

	int l = 0;
	int row;
	row = get_rows(matrix);
	if (row == -1 || row == -2) {
		printf("ошибка чтения матрицы: %d\n", row);
		return ERROR;
	}
	int col;
	col = get_cols(matrix);
	if (col == -1 || col == -2) {
		printf("ошибка чтения матрицы: %d\n", col);
		return ERROR;
	}
	//транспонирование
	transpon(matrix);

	//печать транспонированной матрицы
	print_matrix(col, row, matrix);

	free_matrix(matrix);
	return 0;
}
//транспонирование матрицы

void transpon(Matrix *matrix)
{
	//перемена индексов элементов(транспонирование)
	int i = 0;
	while((*(matrix + i)).val != '0') {
		swap(matrix, i);
		i++;
	}
	//подсчет ненулевых элементов и сортировка
	int *strel;
	strel = consider_struct_element(matrix);
	qsort(matrix, *strel, sizeof(*matrix), comparator);
}


int comparator(const void* v1, const void* v2)
{
 return ((*((Matrix*)v2)).row < (*((Matrix*)v1)).row);
}


int swap(Matrix *matrix, int i)
{
   int temp;
   temp = (*(matrix+i)).row;
   (*(matrix+i)).row = (*(matrix+i)).col;
   (*(matrix+i)).col = temp;
   return 1;
}

void print_matrix(const int col, const int row, const Matrix *matrix) {
	int m = 0;
	int difind;
	double dnull = 0;
	printf("транспонированная матрица: \n");
	for(int i = 0; i < col; i++){
		printf("\n");
		for(int j = 0; j < row; j++){
			if ((*(matrix + m)).col != j){
				printf("%6.2f", dnull);
				continue;
			}
			printf("%6.2f", (*(matrix + m)).val);
			m++;
		}
	}
	printf("\n");
}

int *consider_struct_element(const Matrix *matrix) {
	int *b, p;
	p = 0;
	b = &p;
	while((*(matrix + *b)).val != '0') //подсчет количества элементов
			(*b)++;
	return b;
}

