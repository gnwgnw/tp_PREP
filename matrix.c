#include "matrix.h"
#include <stdlib.h>
#include <ctype.h>

int check(char *buf){
	int i = 0;
	int c;
	int count = 0;
	int flag = 0;
	int state = 0;

	while((c = buf[i]) != '\0'){
		++i;

		if((c == '-' || c == '+') && count == 2 && flag == 0){
			state = 1;
			continue;
		}

		if(c == '.' && ((count == 2 && flag == 0) || (count == 3 && flag == 1))){
			continue;
		}

		if(isspace(c)){
			flag = 0;
			continue;
		}

		if(isdigit(c)){
			if(flag == 0 || state == 1)
				count += 1;
			flag = 1;
			continue;
		}

		count = -1;
		break;
	}

	return count;
}
		
Matrix* create_matrix_from_file(FILE* file){

  	if (file == NULL){
		printf("Error\n");
		exit (1);
		}

	int row = 0;
	int col = 0;
	int number = 0;
	Matrix *matrix;
	int i, j, k;
	double val;
	char buf[256];

	buf[0] = '\0';
	fgets(buf, 256, file);
	if(check(buf) != 1 || sscanf(buf, "%d", &row) != 1){
		printf("Wrong data\n");
		fclose(file);
		exit (1);
	}

	buf[0] = '\0';
	fgets(buf, 256, file);
	if(check(buf) != 1 || sscanf(buf, "%d", &col) != 1){
		printf("Wrong data\n");
		fclose(file);
		exit (1);
	}

	buf[0] = '\0';
	fgets(buf, 256, file);
	if(check(buf) != 1 || sscanf(buf, "%d", &number) != 1){
		printf("Wrong data\n");
		fclose(file);
		exit (1);
	}

	if(!row || !col){
		printf("Wrong data\n");
		fclose(file);
		exit (1);
	}

	if(row * col < number){
		printf("Wrong data\n");
		fclose(file);
		exit (1);
	}
	
	matrix = create_matrix(row, col);

	for(k = 0; k < number; k++){
		buf[0] = '\0';
		fgets(buf, 256, file);

		if(check(buf) != 3 || sscanf(buf, "%d%d%lf", &i, &j, &val) != 3){
			printf("Wrong data\n");
			fclose(file);
			free_matrix(matrix);
			exit (1);
		}
		if(i >= row || j >= col){
			printf("Wrong data\n");
			fclose(file);
			free_matrix(matrix);
			exit (1);
		}
		set_elem(matrix, i, j, val);
	}
	
	int c;

	while((c = fgetc(file)) != EOF)
		if(!isspace(c)){
			printf("Wrong data\n");
			fclose(file);
			free_matrix(matrix);
			exit (1);
		}		
		
	return matrix;
}


Matrix* create_matrix(int row, int col){
 	Matrix *matrix = NULL;
	unsigned i, j;

	if ((matrix = (Matrix*) malloc(sizeof(Matrix*))) == NULL){
		printf("Not enough memory\n");
		exit (1);
   	}

	if ((matrix->array = (double**) malloc(row * sizeof(double*))) == NULL){
		printf("Not enough memory\n");
		exit (1);
   	}

	for (i = 0; i < row; i++){
		if ((matrix->array[i] = (double*) malloc(col * sizeof(double))) == NULL){
			printf("Not enough memory\n");
			exit (1);
   		}
    	}

	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			set_elem(matrix, i, j, 0.0);

	matrix->row = row;
	matrix->col = col;

	return matrix;
}


void free_matrix(Matrix* matrix){
	unsigned i;

	for (i = 0; i < matrix->row; i++)
        	free(matrix->array[i]);

	free(matrix->array);
	free(matrix);
}


double get_elem(Matrix* matrix, int row, int col){
	return matrix->array[row][col];
}


void set_elem(Matrix* matrix, int row, int col, double val){
	matrix->array[row][col] = val;
}


int get_rows(Matrix* matrix){
	return matrix->row;
}


int get_cols(Matrix* matrix){
	return matrix->col;
}
