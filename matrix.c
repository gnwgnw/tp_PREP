#include "matrix.h"
#include <stdlib.h>
#include <ctype.h>

#define A_LOT_OF_ROWS -1
#define NO_ROWS -2
#define A_LOT_OF_COLS -1
#define NO_COLS -2
#define SIZE_BUF 100
#define ERROR -3

int numrows(FILE *);
int numcols(FILE *);

struct Matrix *matrix;
Matrix* create_matrix_from_file(FILE* file)
{
	char buf[SIZE_BUF];
	double *value;
	printf("внутри библиотеки");
	//printf("\n");
	int rows = numrows(file);
	if (rows < 0)
		return NULL;
	int cols = numcols(file);
	if (cols < 0)
		return NULL;

	matrix = create_matrix(rows, cols);
	int numel = 0, w = 0;
	char *pointbuf;
	printf("исходная матрица: \n");
	for (int i = 0; i < rows; i++){
		pointbuf = fgets (buf, SIZE_BUF, file);
		printf("%s\n", buf);
		while ((*(buf + w)) != '\n') {
			if ((*(buf + w) < '0' || *(buf + w) > '9') && *(buf + w) != '.' && *(buf + w) != ' ') {
				printf("некорректный символ: %c\n", *(buf + w));
				return NULL;
			}
			w++;
		}
		int j = 0;
		*value = atof(buf);
		(*(matrix + numel)).val = *value;
		(*(matrix + numel)).row = i;
		(*(matrix + numel)).col = j;
		numel++;
		for (int k = 0; *(buf + k) != '\n'; k++){
			if ((*(buf+k+1)) == '0')
				j++;
			else if ((*(buf + k)) == ' ') { //проверка, на начало числа (пробел перед ним)
				j++;
				*value = atof(buf+k+1);
				(*(matrix + numel)).val = *value;
				(*(matrix + numel)).row = i;
				(*(matrix + numel)).col = j;
				numel++;
			}
		}
		if (j >= cols) {
				printf("нас обманули, элементов больше, чем должно быть, либо лишний знак пунктуации \n");
				return NULL;
		}
	}
	return matrix;
}

Matrix* create_matrix(int row, int col)
{
	Matrix *matrix;
	matrix = (Matrix *) malloc(sizeof(Matrix)*row *col);
	if (matrix == NULL) {
		printf("ошибка выделения памяти");
		return NULL;
	}
	for (int i = 0; i < (row*col); i++) {
		(*(matrix + i)).val = '0';
		(*(matrix + i)).row = 0;
		(*(matrix + i)).col = 0;
	}
	return matrix;
}

int numrows(FILE *file) //подсчет количества строк
	{
	int rows, n, i;
	char *rowsc;
	i = 0;
	fgets (rowsc, 4, file);
	if (fgets == 0)
		printf("ошибка при чтении первой строки");
	while (*(rowsc + i) != '\n') {
		if (*(rowsc + i) < '0' || *(rowsc + i) > '9') {
			printf("ошибка в первой строке файла (количество строк) : %s\n", rowsc);
					return ERROR;
		}
		i++;
		if (i == 3) {
			printf("ошибка в первой строке файла (слишком большое значение) : %s\n", rowsc);
			return ERROR;
		}
	}
	rows = atoi(rowsc);
	printf("количество строк: %d\n",rows);
	return rows;
	}

int numcols(FILE *file)//подсчет количества столбцов
	{
	int n, cols, i;
	char *colsc;
	i = 0;
	fgets(colsc, 4, file);
	if (fgets == 0)
		printf("ошибка при чтении второй строки");
	while (*(colsc + i) != '\n') {
		if (*(colsc + i) < '0' || *(colsc + i) > '9') {
			printf("ошибка во второй строке файла (количество столбцов) : %s\n", colsc);
					return ERROR;
		}
		i++;
		if (i == 3) {
			printf("ошибка во второй строке файла (слишком большое значение) : %s\n", colsc);
			return ERROR;
		}
	}
	cols = atoi(colsc);
	printf("количество столбцов: %d\n", cols);
	return cols;
	}


void free_matrix(Matrix* matrix)
{
	free(matrix);
}

int get_rows(Matrix* matrix) {
	int rows;
	int i = 0;
	int maxrow = -1;
	while((*(matrix+i)).val != '0'){
		if(maxrow < (*(matrix+i)).row)
			maxrow = (*(matrix+i)).row;
		i++;
	}
	if (maxrow == -1) {
		printf("ошибка: странное количество строк, неверная индексация");
		return NO_ROWS;
	}
	if (maxrow > 50) {
		printf("ошибка: странное количество строк, очень большая матрица");
		return A_LOT_OF_ROWS;
	}
	rows = maxrow + 1;
	printf("количесвто строк равно: %d\n",rows);
	return rows;
}


int get_cols(Matrix* matrix) {
	int cols;
	int i = 0;
	int maxcol = -1;
		while((*(matrix+i)).val != '0'){
			if(maxcol <= (*(matrix+i)).col)
				maxcol = (*(matrix+i)).col;
			i++;
		}
		if (maxcol == -1) {
			printf("ошибка: странное количество столбцов, неверная индексация");
			return NO_COLS;
		}
		if (maxcol > 50) {
			printf("ошибка: странное количество столбцов, очень большая матрица");
			return A_LOT_OF_COLS;
		}
		cols = maxcol + 1;
	printf("количесвто столбцов равно: %d\n",cols);
	return cols;
}



