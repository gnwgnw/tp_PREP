#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>

typedef struct Matrix {
    int col;
    int row;
    double val;
} Matrix;

Matrix* create_matrix_from_file(FILE* file); //чтение из файла
Matrix* create_matrix(int row, int col); //создание объекта типа матрицы
void free_matrix(Matrix* matrix); //освобождение памяти из под матрицы
double get_elem(Matrix* matrix, int row, int col); //достать элемент матрицы
void set_elem(Matrix* matrix, int row, int col, double val); //переназначить элемент матрицы
int get_rows(Matrix* matrix); //определить количество строк
int get_cols(Matrix* matrix); //определить количество столбцов

#endif //_MATRIX_H_

