import random


def generate_base_matrix():
    gen_file = open("base_matrix.txt", "w")
    gen_file.write("2\n")
    gen_file.write("2\n")
    gen_file.write("4\n")
    gen_file.write("0 0 7\n")
    gen_file.write("0 1 8\n")
    gen_file.write("1 0 9\n")
    gen_file.write("1 1 8\n")
    gen_file.close()


# Генерация квадратной матрицы
def gen_square_matrix(cnt):
    file_name = "square_matrix" + str(cnt) + ".txt"
    gen_file = open(file_name, "w")
    row_and_col_matrix = random.randint(5, 10)
    numb_not_null = random.randint(1, row_and_col_matrix ** 2)

    gen_file.write(str(row_and_col_matrix) + "\n")
    gen_file.write(str(row_and_col_matrix) + "\n")
    gen_file.write(str(numb_not_null) + "\n")

    set_square_matrix = set()

    while len(set_square_matrix) is not numb_not_null:
        row = random.randint(0, row_and_col_matrix - 1)
        col = random.randint(0, row_and_col_matrix - 1)
        concat_r_c = str(row) + " " + str(col)

        if concat_r_c not in set_square_matrix:
            set_square_matrix.add(concat_r_c)
            value = random.uniform(1.0, 100.0)
            gen_file.write(str(row) + " " + str(col) + " " + str(value) + "\n")
        else:
            continue
    gen_file.close()


def gen_rectangle_matrix(cnt):
    file_name = "rectangle_matrix" + str(cnt) + ".txt"
    gen_file = open(file_name, "w")
    row_matrix = random.randint(5, 10)
    col_matrix = random.randint(5, 10)
    numb_not_null = random.randint(1, row_matrix * col_matrix)

    gen_file.write(str(row_matrix) + "\n")
    gen_file.write(str(col_matrix) + "\n")
    gen_file.write(str(numb_not_null) + "\n")

    set_square_matrix = set()

    while len(set_square_matrix) is not numb_not_null:
        row = random.randint(0, row_matrix - 1)
        col = random.randint(0, col_matrix - 1)
        concat_r_c = str(row) + " " + str(col)

        if concat_r_c not in set_square_matrix:
            set_square_matrix.add(concat_r_c)
            value = random.uniform(1.0, 100.0)
            gen_file.write(str(row) + " " + str(col) + " " + str(value) + "\n")
        else:
            continue
    gen_file.close()


def gen_zero_inp():
    file_name = "zero_inp_matrix.txt"
    gen_file = open(file_name, "w")
    row_matrix = random.randint(5, 10)
    col_matrix = random.randint(5, 10)
    numb_not_null = random.randint(1, row_matrix * col_matrix)

    gen_file.write(str(row_matrix) + "\n")
    gen_file.write(str(numb_not_null) + "\n")
    gen_file.write(str(0) + "\n")

    set_square_matrix = set()

    while len(set_square_matrix) is not numb_not_null:
        row = random.randint(0, row_matrix - 1)
        col = random.randint(0, col_matrix - 1)
        concat_r_c = str(row) + " " + str(col)

        if concat_r_c not in set_square_matrix:
            set_square_matrix.add(concat_r_c)
            value = random.uniform(1.0, 100.0)
            gen_file.write(str(row) + " " + str(col) + " " + str(value) + "\n")
        else:
            continue
    gen_file.close()


def gen_intp_number_with_wtf():
    file_name = "WTF_matrix.txt"
    gen_file = open(file_name, "w")
    list_wtf = [',', ';', '!', '&', 'w', 't', 'f', '_', '?']

    row_matrix = random.randint(5, 10)
    col_matrix = random.randint(5, 10)
    numb_not_null = random.randint(1, row_matrix * col_matrix)

    gen_file.write(str(row_matrix) + "\n")
    gen_file.write(str(col_matrix) + "\n")
    gen_file.write(str(numb_not_null) + "\n")

    set_square_matrix = set()

    while len(set_square_matrix) is not numb_not_null:
        row = random.randint(0, row_matrix - 1)
        col = random.randint(0, col_matrix - 1)
        concat_r_c = str(row) + " " + str(col)
        numb_wtf = random.randint(0, len(list_wtf) - 1)

        if concat_r_c not in set_square_matrix:
            set_square_matrix.add(concat_r_c)
            value = random.uniform(1.0, 100.0)
            gen_file.write(str(row) + " " + str(col) + " " + list_wtf[numb_wtf] + str(value) + "\n")
        else:
            continue
    gen_file.close()


def gen_inp_little_data():
    file_name = "little_data_matrix.txt"
    gen_file = open(file_name, "w")

    row_matrix = random.randint(5, 10)
    col_matrix = random.randint(5, 10)
    numb_not_null = random.randint(10, row_matrix * col_matrix)

    gen_file.write(str(row_matrix) + "\n")
    gen_file.write(str(col_matrix) + "\n")
    gen_file.write(str(numb_not_null) + "\n")

    set_square_matrix = set()

    while len(set_square_matrix) is not numb_not_null-5:
        row = random.randint(0, row_matrix - 1)
        col = random.randint(0, col_matrix - 1)
        concat_r_c = str(row) + " " + str(col)

        if concat_r_c not in set_square_matrix:
            set_square_matrix.add(concat_r_c)
            value = random.uniform(1.0, 100.0)
            gen_file.write(str(row) + " " + str(col) + " " + str(value) + "\n")
        else:
            continue
    gen_file.close()


def gen_repeat_index():
    file_name = "repeat_data_matrix.txt"
    gen_file = open(file_name, "w")

    row_matrix = random.randint(5, 10)
    col_matrix = random.randint(5, 10)
    numb_not_null = random.randint(10, row_matrix * col_matrix)

    gen_file.write(str(row_matrix) + "\n")
    gen_file.write(str(col_matrix) + "\n")
    gen_file.write(str(numb_not_null) + "\n")

    set_square_matrix = set()

    while len(set_square_matrix) is not numb_not_null:
        row = random.randint(0, row_matrix - 1)
        col = random.randint(0, col_matrix - 1)
        concat_r_c = str(row) + " " + str(col)

        if concat_r_c not in set_square_matrix:
            set_square_matrix.add(concat_r_c)
            value = random.uniform(1.0, 100.0)
            gen_file.write(str(row) + " " + str(col) + " " + str(value) + "\n")
            gen_file.write(str(row) + " " + str(col) + " " + str(value) + "\n")
        else:
            continue
    gen_file.close()


def gen_overload_integer():
    file_name = "overload_int.txt"
    gen_file = open(file_name, "w")

    row_matrix = random.randint(5, 10)
    col_matrix = random.randint(5, 10)
    numb_not_null = random.randint(10, row_matrix * col_matrix)

    gen_file.write(str(2147483648) + "\n")
    gen_file.write(str(214748364745345534) + "\n")
    gen_file.write(str(numb_not_null) + "\n")

    set_square_matrix = set()

    while len(set_square_matrix) is not numb_not_null:
        row = random.randint(0, row_matrix - 1)
        col = random.randint(0, col_matrix - 1)
        concat_r_c = str(row) + " " + str(col)

        if concat_r_c not in set_square_matrix:
            set_square_matrix.add(concat_r_c)
            value = random.uniform(1.0, 100.0)
            gen_file.write(str(row) + " " + str(col) + " " + str(value) + "\n")
            gen_file.write(str(row) + " " + str(col) + " " + str(value) + "\n")
        else:
            continue
    gen_file.close()


# Генерация хороших матрицц
def generate_good_input_matrix(cnt):
    gen_square_matrix(cnt)
    gen_rectangle_matrix(cnt)


def generate_bad_input_matrix():
    gen_zero_inp()
    gen_intp_number_with_wtf()
    gen_inp_little_data()
    gen_repeat_index()
    gen_overload_integer()

if __name__ == "__main__":

    generate_base_matrix()

    for i in range(10):
        generate_good_input_matrix(i)

    generate_bad_input_matrix()


2147483647





