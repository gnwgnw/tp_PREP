#include "matrix.h"

bool check_dimension(int dim)
{
	if ((dim <= 0) || (dim > INT_MAX))
	{
		printf("Wrong value of matrix dimension.\n");
		return false;
	}
	return true;
}

bool check_index(int dim, int orig)
{
	if ((dim > orig) || (dim < 0))
	{
		printf("Array index out of bounds.\n");
		return false;
	}
	return true;
}

void set_elem(Matrix *matrix, int row, int col, double val)
{
	if (!matrix)
	{
		printf("Can't set element - no matrix.\n");
		return;
	}
	if ((!check_index(row, matrix->row)) || (!check_index(col, matrix->col)))
	{
		printf("Can't set element.\n");
		return;
	}
	matrix->matrix[row][col] = val;
	return;
}

double get_elem(Matrix *matrix, int row, int col)
{
	if (!matrix)
	{
		printf("Can't get element - no matrix.\n");
		return 0;
	}
	if ((!check_index(row, matrix->row)) || (!check_index(col, matrix->col)))
	{
		printf("Can't get element.\n");
		return 0;
	}
	return matrix->matrix[row][col];
}
void init_matrix(Matrix *m)
{
	int i, j;
	for (i = 0; i < m->row; i++)
	{
		for (j = 0; j < m->col; j++)
		{
			set_elem(m, i, j, 0);
		}
	}
	return;
}
Matrix* create_matrix(int row, int col)
{
	int i;
	Matrix* m = (Matrix*)malloc(sizeof(Matrix));
	if ((!check_dimension(row)) || (!check_dimension(col)))
	{
		printf("Caught error of wrong dimension value.\n");
		return NULL;
	}
	m->row = row;
	m->col = col;
	m->matrix = malloc(row * sizeof(double *));
	if (!m->matrix)
	{
		printf("Memory allocation error.\n");
		return NULL;
	}
	for (i = 0; i < row; i++)
	{
		m->matrix[i] = malloc(col * sizeof(double));
		if (!m->matrix[i])
		{
			printf("Memory allocation error.\n");
			free_matrix(m);
		}
	}
	init_matrix(m); // it is made to prevent existence of rubbish in matrix
	return m;
}

void free_matrix(Matrix *matrix)
{
	int i;
	if (matrix)
	{
		for (i = 0; i < matrix->row; i++)
			free(matrix->matrix[i]);
		free(matrix->matrix);
		free(matrix);
	}
	return;
}

int get_rows(Matrix *matrix)
{
	return matrix->row;
}
int get_cols(Matrix *matrix)
{
	return matrix->col;
}

int count_lexemes(char *str)
{
	int count = 0;
	char workstr[strlen(str)];
	if (snprintf(workstr, strlen(str), "%s", str) == -1)
	{
		printf("Some error occured.\n");
		return 0;
	}
	char *lexem = strtok(workstr, " ");
	if (lexem == NULL)
		return 0;
	else
	{
		while (lexem != NULL)
		{
			count++;
			lexem = strtok(NULL, " ");
		}
	}
	return count;
}

bool check_string(char *str, int checkcount)
{
	int count = count_lexemes(str);
	if (checkcount != count)
	{
		printf("Incorrect data.\n");
		return false;
	}
	char workstr[strlen(str)];
	if (snprintf(workstr, strlen(str), "%s", str) == -1)
	{
		printf("Some error occured.\n");
		return false;
	}
	char *lexem = strtok(workstr, " ");
	if (lexem == NULL)
		return false;
	else
	{
		count = 1;
		while ((lexem != NULL) && (count < checkcount))
		{
			if (strcmp(lexem, "0") != 0)
			{
				int val = atof(lexem);
				if (val == 0)
				{
					printf("Incorrect data.\n");
					return false;
				}
			}
			lexem = strtok(NULL, " \n");
			count++;
		}
	}
	return true;
}

bool string_to_param(char *str, int *param)
{
	if (!check_string(str, 1))
	{
		printf("Can't convert to param - incorrect string.\n");
		return false;
	}
	char workstr[strlen(str)];
	if (snprintf(workstr, strlen(str), "%s", str) == -1)
	{
		printf("Some error occured.\n");
		return false;
	}
	char *lexem = strtok(workstr, " ");
	if (strcmp(lexem, "0") != 0)
	{
		int val = atof(lexem);
		if (val == 0)
		{
			printf("Incorrect data.\n");
			return false;
		}
		*param = val;
		return true;
	}
	*param = atof(lexem);
	return true;
}

bool string_to_params(char *str, int *row, int *col, double *val)
{
	if (!check_string(str, 3))
	{
		printf("Can't convert to params - incorrect string.\n");
		return false;
	}
	char workstr[strlen(str)];
	if (snprintf(workstr, strlen(str), "%s", str) == -1)
	{
		printf("Some error occured.\n");
		return false;
	}
	char *lexem = strtok(workstr, " ");
	*row = atoi(lexem);
	lexem = strtok(NULL, " ");
	*col = atoi(lexem);
	lexem = strtok(NULL, " ");
	*val = atof(lexem);
	return true;
}

Matrix* create_matrix_from_file(FILE *file)
{
	int rows, cols;
	int n; // amount of not null elements
	int count = 0; // current value of inserted elements
	if (file == NULL)
	{
		printf("No initial file.\n");
		return NULL;
	}
	char str[STRING_LENGTH];
	if (fgets(str, STRING_LENGTH, file) != NULL)
	{
		if (!string_to_param(str, &rows))
		{
			printf("Incorrect value of rows amount.\n");
			return NULL;
		}
	}
	if (fgets(str, STRING_LENGTH, file) != NULL)
	{
		if (!string_to_param(str, &cols))
		{
			printf("Incorrect value of cols amount.\n");
			return NULL;
		}
	}
	if (fgets(str, STRING_LENGTH, file) != NULL)
	{
		if (!string_to_param(str, &n))
		{
			printf("Incorrect value of not null elements amount.\n");
			return NULL;
		}
	}

	if (n > (rows*cols))
	{
		printf("Incorrect value of not null elements amount.\n");
		return NULL;
	}
	Matrix *m = create_matrix(rows, cols);
	if (!m)
	{
		printf("Memory allocation error.\n");
		return NULL;
	}
	while ((!feof(file)) && (count < n))
	{
		int row, col;
		double val;
		if (fgets(str, INT_MAX, file) != NULL)
		{
			if (!string_to_params(str, &row, &col, &val))
			{
				printf("Incorrect data.\n");
				free_matrix(m);
				return NULL;
			}
		}

		set_elem(m, row, col, val);
		count++;
	}
	return m;
}
