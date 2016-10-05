#include "matrix.h"

int main(int argc, char* argv[])
{
	//TODO
	printf("%s\n", argv[1]);
	printf("%s\n", argv[2]);
	FILE* file1 = fopen(argv[1], "r");
	Matrix* matrix1 = create_matrix_from_file(file1);

	FILE* file2 = fopen(argv[2], "r");
	Matrix* matrix2 = create_matrix_from_file(file2);

	int rows_1 = get_rows(matrix1);
	int cols_1 = get_cols(matrix1);
	int rows_2 = get_rows(matrix2);
	int cols_2 = get_cols(matrix2);
	for (int i = 0; i < rows_1; i++) {
		for (int j = 0; j < cols_1; j++)
			printf("%.3f ", get_elem(matrix1, i ,j));
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < rows_1; i++) {
                for (int j = 0; j < cols_1; j++) 
                        printf("%.3f ", get_elem(matrix2, i ,j));
                printf("\n");
        }
        printf("\n");

	if ((rows_1 != rows_2) || (cols_1 != cols_2)) {
		printf("Ошибка. Разные размеры матрицы \n");
		return -1;
	}
	for (int i = 0; i < rows_1; i++) {
		for (int j = 0; j < cols_1; j++) {
			printf("%.3f ",  get_elem(matrix1, i ,j) +  get_elem(matrix2, i ,j));
		}
		printf("\n");
	}
	fclose(file1);
	fclose(file2);
	free_matrix(matrix1);
	free_matrix(matrix2);
	return 0;
}
