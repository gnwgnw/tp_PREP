#include "matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <file_name>\n", argv[0]);
		return EXIT_FAILURE;
	}

	FILE* f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("Error while open file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	Matrix* M = create_matrix_from_file(f);
	fclose(f);

	uint32_t rows = get_rows(M);
	uint32_t cols = get_cols(M);

	// Print matrix from file
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%f ", get_elem(M, i, j));
		}
		printf("\n");
	}

	Matrix* M_t = create_matrix(cols, rows);



	//Transporation
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			set_elem(M_t, i, j, get_elem(M, j, i));
		}
	}

	// Print transporated
	printf("\n\n\n");
	for (int i = 0; i < cols; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			printf("%f ", get_elem(M_t, i, j));
		}
		printf("\n");
	}


	free_matrix(M);
	free_matrix(M_t);
	return 0;
}