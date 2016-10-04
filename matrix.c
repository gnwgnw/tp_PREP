#include "matrix.h"
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef enum dz2_err{
    DZ2_OK = 0,
    DZ2_ENOMEM = -1,
    DZ2_BAD_FILE = -2,
    DZ2_NULL_POINTER = -3,
    DZ2_DIV_0 = -4,
    DZ2_BAD_LEN_STRING_FOR_INTEGER = -5,
    DZ2_BAD_INP_NUMB = -6,
    DZ2_ERROR_SIZE = -7,
    DZ2_BAD_SPRINTF = -8,
    DZ2_ELEM_WAS_ENTERED = -9
}dz2_err_t;

static const char* const dz2_err_str[] = {
    "DZ2_OK",
    "DZ2_ENOMEM",
    "DZ2_BAD_FILE",
    "DZ2_NULL_POINTER",
    "DZ2_DIV_0",
    "DZ2_BAD_LEN_STRING_FOR_INTEGER",
    "DZ2_BAD_INP_NUMB",
    "DZ2_ERROR_SIZE",
    "DZ2_BAD_SPRINTF",
    "DZ2_ELEM_WAS_ENTERED",
    0
};

static void print_err_dz2(const char *func, const char *filename, int line_in_code, dz2_err_t scode_err){
    printf("[%s:%d] %s %d: %s\n ", filename, line_in_code, func, scode_err, dz2_err_str[-scode_err]);
}

/*
static dz2_err_t print_matrix(const Matrix *matrix, const int len_matrix){
    if(!matrix){
        print_err_dz2("add_element", __FILE__, __LINE__, DZ2_NULL_POINTER);
        return DZ2_NULL_POINTER;
    }

    printf("TABLE:\n");
    for(int i = 0; i < len_matrix; ++i){
        printf("%d  %d  %f\n", matrix[i].ind_row, matrix[i].ind_col, matrix[i].value);
    }

    return DZ2_OK;
}
*/

static int len_integer(){
    char r_c[20] = "";
    int check = 0;
    int len_int = 0;

    check = sprintf(r_c,"%d", INT_MAX);

    if(check<=0){
        print_err_dz2("len_integer", __FILE__, __LINE__, DZ2_BAD_SPRINTF);
        return DZ2_BAD_SPRINTF;
    }

    for(int i = 0; i < 20 && r_c[i] != '\0'; ++i){
        ++len_int;
    }

    return len_int;
}

static int len_double(){

    char d_str[350] = "";
    int check = 0;
    int len_dbl = 0;

    check = sprintf(d_str,"%f", DBL_MAX);

    if(check<=0){
        print_err_dz2("len_double", __FILE__, __LINE__, DZ2_BAD_SPRINTF);
        return DZ2_BAD_SPRINTF;
    }

    for(int i = 0; i < 350 && d_str[i] != '\0'; ++i){
        ++len_dbl;
    }

    return len_dbl;
}

//конвертируем троку в int с провреками на правилность ввода
//code use: true - string have \0 on end, false - else , int code_use
static dz2_err_t string_to_int_from_file(const char *string_int, int *number, bool str_zero_end){
    int len_int = len_integer(); //Для привязки к разрядности ОС
    int len_read = 0;
    if(len_int <= 0){
        print_err_dz2("string_to_int_from_file", __FILE__, __LINE__, DZ2_BAD_SPRINTF);
        return DZ2_BAD_SPRINTF;
    }

    for(int i = 0; i < len_int && string_int[i] != '\0' && string_int[i] != '\n' ; ++i){
        //проверка. в строке только числа?
        if(string_int[i] < '0' || string_int[i]>'9'){
            print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_INP_NUMB);
            printf("input string have \"%c\"\n",string_int[i]);
            printf("string for convert to int(int rows or int cols): %s\n", string_int);
            return DZ2_BAD_INP_NUMB;
        }
        ++len_read; //количество считываемых байтов
    }
    //проверка на пустую строку
    if(len_read == 0){
        print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_LEN_STRING_FOR_INTEGER);
        puts("Input empty string for rows or cols\n");
        return DZ2_BAD_LEN_STRING_FOR_INTEGER;
    }
    //проверка на переполненную строку и одновременно на пусту
    char *symbol_new_line = NULL;
    if(str_zero_end){
        symbol_new_line = strchr(string_int, '\0');
    }
    else{
        symbol_new_line = strchr(string_int, '\n');
    }

    if(!symbol_new_line || symbol_new_line - string_int == 0){
        print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_INP_NUMB);
        puts("Maybe entered a string more than len(max(int))");
        printf("string for convert to int(int rows or int cols): %s\n", string_int);
        return DZ2_BAD_INP_NUMB;
    }

    //навсякий случай, чет не догнал почему "if" выше отрабатывает и это. но мало ли че;)
    if(len_read > len_int){
        print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_INP_NUMB);
        puts("Entered a number more than max(int)");
        printf("string for convert to int(int rows or int cols): %s\n", string_int);
        return DZ2_BAD_INP_NUMB;
    }
    //проверка переполнение int
    *number = atoi(string_int);
    if(*number < 0){
        print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_INP_NUMB);
        puts("Entered a number more than max(int)");
        puts("MAY BE OVERLOAD INTEGER");
        printf("String for convert to int(int rows or int cols): %s\n", string_int);
        return DZ2_BAD_INP_NUMB;
    }

    return DZ2_OK;
}

static dz2_err_t string_to_dbl_from_file(const char *string_double, double *number){
    int len_dbl = len_double();
    int len_read = 0;
    if(len_dbl <= 0){
        print_err_dz2("string_to_dbl_from_file", __FILE__, __LINE__, DZ2_BAD_SPRINTF);
        return DZ2_BAD_SPRINTF;
    }

    for(int i = 0; i < len_dbl && string_double[i] != '\0' && string_double[i] != '\n' ; ++i){
        //проверка. в строке только числа?
        if((string_double[i] < '0' || string_double[i]>'9')){
            if(string_double[i] != '.'){
                print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_INP_NUMB);
                printf("input string have \"%c\"\n",string_double[i]);
                printf("string for convert to int(int rows or int cols): %s\n", string_double);
                return DZ2_BAD_INP_NUMB;
            }
        }
        ++len_read; //количество считываемых байтов
    }
    //проверка на пустую строку
    if(len_read == 0){
        print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_LEN_STRING_FOR_INTEGER);
        puts("Input empty string for rows or cols\n");
        return DZ2_BAD_LEN_STRING_FOR_INTEGER;
    }
    //проверка на переполненную строку и одновременно на пустую

    char *symbol_end_line = strchr(string_double, '\0');

    if(!symbol_end_line || symbol_end_line - string_double == 0){
        print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_INP_NUMB);
        puts("Maybe entered a string more than len(max(int))");
        printf("string for convert to int(int rows or int cols): %s\n", string_double);
        return DZ2_BAD_INP_NUMB;
    }

    //навсякий случай, чет не догнал почему "if" выше отрабатывает и это. но мало ли че;)
    if(len_read > len_dbl){
        print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_INP_NUMB);
        puts("Entered a number more than max(int)");
        printf("string for convert to int(int rows or int cols): %s\n", string_double);
        return DZ2_BAD_INP_NUMB;
    }
    //проверка вощможности перевода в double
    *number = atof(string_double);
    if(*number <= 0){
        print_err_dz2("get_inp_row_or_col_from_file", __FILE__, __LINE__, DZ2_BAD_INP_NUMB);
        puts("Entered a number more than max(int)");
        printf("String for convert to int(int rows or int cols): %s\n", string_double);
        return DZ2_BAD_INP_NUMB;
    }

    return DZ2_OK;
}

static dz2_err_t read_number(FILE *file, int *number){
    if(!file){
        print_err_dz2("read_number", __FILE__, __LINE__, DZ2_NULL_POINTER);
        return DZ2_NULL_POINTER;
    }
    int len_int = len_integer(); //Для привязки к разрядности ОС
    char number_str[len_int+2];

    char *check_ret = fgets(number_str, len_int+2, file);
    if(!check_ret){
        print_err_dz2("read_number", __FILE__, __LINE__, DZ2_BAD_INP_NUMB);
        return DZ2_BAD_INP_NUMB;
    }

    dz2_err_t dz2_err_ret = string_to_int_from_file(number_str, number, false);
    if(dz2_err_ret){
        print_err_dz2("read_number", __FILE__, __LINE__, dz2_err_ret);
        return dz2_err_ret;
    }

    return DZ2_OK;
}

static dz2_err_t get_elem_from_string_file(char *string, int *row, int *col, double *value){

    int cnt_key_for_read = 0; //1 - for read row, 2 - for read col, 3 - for read double, else - bad input file

    char *sub_str = strtok(string, " \n");

    while(sub_str){
        ++cnt_key_for_read;

        if(cnt_key_for_read == 1){
            dz2_err_t dz2_err_ret = string_to_int_from_file(sub_str, row, true);
            if(dz2_err_ret){
                print_err_dz2("add_elements", __FILE__, __LINE__, dz2_err_ret);
                return dz2_err_ret;
            }
        }
        else if(cnt_key_for_read == 2){
            dz2_err_t dz2_err_ret = string_to_int_from_file(sub_str, col, true);
            if(dz2_err_ret){
                print_err_dz2("add_elements", __FILE__, __LINE__, dz2_err_ret);
                return dz2_err_ret;
            }
        }
        else if(cnt_key_for_read == 3){
            dz2_err_t dz2_err_ret = string_to_dbl_from_file(sub_str, value);
            if(dz2_err_ret){
                print_err_dz2("add_elements", __FILE__, __LINE__, dz2_err_ret);
                return dz2_err_ret;
            }
        }
        else{
            print_err_dz2("add_elements", __FILE__, __LINE__, DZ2_BAD_FILE);
            puts("A lot of input numbers");
            return DZ2_BAD_FILE;
        }

        sub_str = strtok(NULL, " \n");
    }

    //проверка того, что считалось именно 3 подстроки(ни меньше, ни больше)
    if(cnt_key_for_read != 3){
        print_err_dz2("add_elements", __FILE__, __LINE__, DZ2_BAD_FILE);
        return DZ2_BAD_FILE;
    }

    return DZ2_OK;
}

static dz2_err_t init_zero_matrix(Matrix *matrix, const int rows, const int cols){
    if(!matrix){
        print_err_dz2("add_element", __FILE__, __LINE__, DZ2_NULL_POINTER);
        return DZ2_NULL_POINTER;
    }

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            matrix[i*cols + j].ind_row = i;
            matrix[i*cols + j].ind_col = j;
            matrix[i*cols + j].size_rows = rows;
            matrix[i*cols + j].size_cols = cols;
            matrix[i*cols + j].value = 0;


        }
    }

    return DZ2_OK;
}

static dz2_err_t add_element(Matrix *matrix, const int row, const int col, const double value){
    if(!matrix){
        print_err_dz2("add_element", __FILE__, __LINE__, DZ2_NULL_POINTER);
        return DZ2_NULL_POINTER;
    }

    if(row >= matrix[0].size_rows || col >= matrix[0].size_cols){
        print_err_dz2("add_element", __FILE__, __LINE__, DZ2_ERROR_SIZE);
        return DZ2_ERROR_SIZE;
    }

    if(matrix[row*matrix[0].size_cols+col].value != 0.){
        print_err_dz2("add_element", __FILE__, __LINE__, DZ2_ELEM_WAS_ENTERED);
        printf("%d %d - %f\n",row, col, matrix[row*col+col].value);
        return DZ2_ELEM_WAS_ENTERED;
    }

    matrix[row*matrix[0].size_cols+col].value = value;

    return DZ2_OK;
}
/*
static dz2_err_t sort_matrix(Matrix *matrix, const int nonzero){
    if(!matrix){
        print_err_dz2("add_element", __FILE__, __LINE__, DZ2_NULL_POINTER);
        return DZ2_NULL_POINTER;
    }

    for(int i = 0; i < nonzero-1; ++i){
        bool swapped = false;
        for(int j = 0; j < nonzero-i-1; j++){
            if(matrix[j].ind_row > matrix[j+1].ind_row){
                Matrix tmp = matrix[j];
                matrix[j] = matrix[j+1];
                matrix[j+1] = tmp;
                swapped = true;
            }
        }

        if(!swapped){
            break;
        }
    }

    for(int i = 0; i < nonzero-1; ++i){
        bool swapped = false;
        for(int j = 0; j < nonzero-i-1; j++){
            if(matrix[j].ind_row == matrix[j+1].ind_row){
                if(matrix[j].ind_col > matrix[j+1].ind_col){
                    Matrix tmp = matrix[j];
                    matrix[j] = matrix[j+1];
                    matrix[j+1] = tmp;
                    swapped = true;
                }
            }
        }

        if(!swapped){
            break;
        }
    }


    return DZ2_OK;
}*/

static dz2_err_t read_elements_from_file_and_adding_to_matrix(Matrix *matrix, FILE *file, const int nonzero){
    if(!matrix || !file){
        print_err_dz2("add_elements", __FILE__, __LINE__, DZ2_NULL_POINTER);
        return DZ2_NULL_POINTER;
    }
    if(nonzero == 0){
        print_err_dz2("add_elements", __FILE__, __LINE__, DZ2_ERROR_SIZE);
        return DZ2_ERROR_SIZE;
    }

    int len_int = len_integer();
    int len_dbl = len_double();
    int len_all = len_int * 2 + len_dbl + 2 + 1 + 2; // 2 - int, 1 - dbl, 2 - space, 1 - \0, +2 c запасиком; )
    int row = 0;
    int col = 0;
    double value = 0.;
    int cnt_read_string = 0;

    char str_all[len_all];
    char *check_ret = NULL;

    while(!feof(file)){

        check_ret = fgets(str_all, len_all, file);
        if(str_all[0] == '\n' || str_all[0] == '\0'){
            puts("Empty string");
            break;
        }
        if(!check_ret){
            print_err_dz2("add_elements", __FILE__, __LINE__, DZ2_BAD_FILE);
            return DZ2_BAD_FILE;
        }

        dz2_err_t dz2_err_err = get_elem_from_string_file(str_all,&row, &col, &value);
        if(dz2_err_err){
            print_err_dz2("add_elements", __FILE__, __LINE__, dz2_err_err);
            return dz2_err_err;
        }

        dz2_err_err = add_element(matrix, row, col, value);
        if(dz2_err_err){
            print_err_dz2("add_elements", __FILE__, __LINE__, dz2_err_err);
            return dz2_err_err;
        }

        ++cnt_read_string;
        //        printf("cnt_read_string = %d,row = %d;   col = %d;  val = %f\n", cnt_read_string, row, col,value);
        //Если считали необходимое количество строк
        if(cnt_read_string == nonzero){
            break;
        }
    }
    //проверка на точное количество считанных строк
    if(cnt_read_string != nonzero){
        print_err_dz2("add_elements", __FILE__, __LINE__, DZ2_BAD_FILE);
        puts("not enough input");
        return DZ2_BAD_FILE;
    }

    //проверка есть ли ещё строки после необходимого количества считанных
    check_ret = fgets(str_all, len_all, file);
    if(check_ret){
        printf("h1\n");
        if(str_all[0] != '\n' && str_all[0] != '\0'){
            print_err_dz2("add_elements", __FILE__, __LINE__, DZ2_BAD_FILE);
            return DZ2_BAD_FILE;
        }
    }

    return DZ2_OK;
}

Matrix* create_matrix_from_file(FILE* file){
    if(!file){
        print_err_dz2("create_matrix_from_file", __FILE__, __LINE__, DZ2_BAD_FILE);
        return NULL;
    }

    int rows = 0;
    int cols = 0;
    int nonzero = 0;
    int len_matrix = 0;

    dz2_err_t dz2_err_ret = read_number(file, &rows);
    if(dz2_err_ret || rows == 0){
        puts("BAD ROWS");
        return NULL;
    }
//    printf("rows = %d\n", rows);

    dz2_err_ret = read_number(file, &cols);
    if(dz2_err_ret || cols == 0){
        puts("BAD COLS");
        return NULL;
    }
//    printf("cols = %d\n", cols);

    dz2_err_ret = read_number(file, &nonzero);
    if(dz2_err_ret || nonzero == 0){
        puts("BAD NONEZERO");
        return NULL;
    }
//    printf("nonzero = %d\n", nonzero);

    len_matrix = rows * cols;
//    printf("len_matrix = %d\n", len_matrix);
    Matrix *matrix = malloc(sizeof(Matrix) * len_matrix);

    if(!matrix){
        print_err_dz2("create_matrix_from_file", __FILE__, __LINE__, DZ2_ENOMEM);
        free_matrix(matrix);
        return NULL;
    }
    dz2_err_ret = init_zero_matrix(matrix, rows, cols);

    dz2_err_ret = read_elements_from_file_and_adding_to_matrix(matrix, file, nonzero);
    if(dz2_err_ret){
        print_err_dz2("create_matrix_from_file", __FILE__, __LINE__, dz2_err_ret);
        free_matrix(matrix);
        return NULL;
    }


//    dz2_err_ret = sort_matrix(matrix, nonzero);
//    if(dz2_err_ret){
//        print_err_dz2("create_matrix_from_file", __FILE__, __LINE__, dz2_err_ret);
//        free_matrix(matrix);
//        return NULL;
//    }

//    print_matrix(matrix, len_matrix);

    return matrix;

}

Matrix* create_matrix(int row, int col){

    int len_matrix =  row * col;
    Matrix *matrix = malloc(sizeof(Matrix) * len_matrix);

    if(!matrix){
        print_err_dz2("create_matrix", __FILE__, __LINE__, DZ2_ENOMEM);
        free_matrix(matrix);
        return NULL;
    }

    dz2_err_t dz2_err_ret = init_zero_matrix(matrix, row, col);
    if(dz2_err_ret){
        print_err_dz2("create_matrix", __FILE__, __LINE__, dz2_err_ret);
        free_matrix(matrix);
        return NULL;
    }

    return matrix;
}

void free_matrix(Matrix* matrix){
    free(matrix);
}

double get_elem(Matrix* matrix, int row, int col){
    if(!matrix){
        print_err_dz2("create_matrix", __FILE__, __LINE__, DZ2_NULL_POINTER);
        free_matrix(matrix);
        return 0;
    }

    if(row >= matrix[0].size_rows || col >= matrix[0].size_cols){
        print_err_dz2("create_matrix", __FILE__, __LINE__, DZ2_ERROR_SIZE);
        free_matrix(matrix);
        return 0;
    }

    return matrix[row*col+col].value;
}

void set_elem(Matrix* matrix, int row, int col, double val){
        if(!matrix){
            print_err_dz2("set_elem", __FILE__, __LINE__, DZ2_NULL_POINTER);
            free_matrix(matrix);
        }

        if(row >= matrix[0].size_rows || col >= matrix[0].size_cols){
            print_err_dz2("set_elem", __FILE__, __LINE__, DZ2_ERROR_SIZE);
            return;
        }
        matrix[row*col+col].value = val;
}

int get_rows(Matrix* matrix){

    if(!matrix){
        print_err_dz2("get_rows", __FILE__, __LINE__, DZ2_NULL_POINTER);
        free_matrix(matrix);
        return 0;
    }

    return matrix[0].size_rows;
}

int get_cols(Matrix* matrix){

    if(!matrix){
        print_err_dz2("get_rows", __FILE__, __LINE__, DZ2_NULL_POINTER);
        free_matrix(matrix);
        return 0;
    }

    return matrix[0].size_cols;
}




