#include <stdio.h>
#include "matrix.h"

double get_max_norm(double *norms, int n)
{
	int i;
	double max = norms[0];
	for (i = 1; i < n; i++)
	{
		if (norms[i] > max)
		{
			max = norms[i];
		}
	}
	return max;
}

double max_norm(Matrix *matr)
{
	int i, j;

	double norms[get_rows(matr)];
	for (i = 0; i < get_rows(matr); i++)
	{
		norms[i] = 0;
	}
	for (i = 0; i < get_rows(matr); i++)
	{
		double count = 0.0;
		for (j = 0; j < get_cols(matr); j++)
		{
			double elem = get_elem(matr, i, j);
			if (elem < 0)
				elem = elem * (-1); // in order not to include math.h
			count = count + elem;
		}
		norms[i] = count;
	}
	return get_max_norm(norms, get_rows(matr));
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Wrong amount of parameters.\n");
		return 0;
	}
	Matrix *m = NULL;
	FILE *f = fopen(argv[1], "r");
	m = create_matrix_from_file(f);
	fclose(f);
	if (m != NULL)
	{
		printf("%lf\n", max_norm(m));
		free_matrix(m);
	}
	return 0;
}