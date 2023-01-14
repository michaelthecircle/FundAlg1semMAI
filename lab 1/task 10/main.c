#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#define eps 0.000001
typedef enum Type_of_Fails {
    memory_allocation_fail,
    wrong_launch,
    wrong_flag,
    wrong_params,
    wrong_params_mult,
    wrong_params_determ
}Fails;
 
double** create_matrix(Fails* status, int size_x, int size_y, int flag);
void clean_memo_matrix(double** mat, int n);
void print_matrix(double** mat, int size_x, int size_y);
void mult_matrix(double** mat_1, double** mat_2, double** mat_out, int x, int y, int z);
double gauss(double** matrix, double** matrix_c, int size);
void flag_a(Fails*);
void flag_b(Fails*, int is_flag_c);
void flag_c(Fails* status, double** matrix, int size);
 
void swap(double* a, double* b) {
    double c = *a;
    *a = *b;
    *b = c;
}
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    Fails status;
    int res_flag = 0;
    if (argc != 2) status = wrong_launch;
    else {
        char symb = *argv[1];
        if (symb == 'a') {
            flag_a(&status);
        }
        else if (symb == 'b') {
            flag_b(&status, 0);
        }
        else if (symb == 'c') {
            //flag_c(&status); для чистого запуска флага с, код в самом низу файла
            flag_b(&status, 1);
        }
        else {
            status = wrong_flag;
        }
    }
    switch(status) {
        case wrong_params:
            printf("Неверный ввод параметров\n");
            break;
        case wrong_params_mult:
            printf("Неверные параметры для размера матрицы при умножении(стобец 1 = ряд 2)\n");
            break;
        case wrong_params_determ:
            printf("Неверные параметры для поиска определителя (ряд = стобец)\n");
        case memory_allocation_fail:
            printf("Ошибка выделения памяти\n");
            break;
        case wrong_launch:
            printf("Неверный запуск программы!\nПример правильного: ./task a\n");
            break;
        case wrong_flag:
            printf("Неверный флаг\n");
            break;
        default:
            break;
    }
    return 0;
}
 
double** create_matrix(Fails* status, int size_x, int size_y, int flag) {
    double A = -100.0; //min range gen
    double B = 100.0; //max range gen
    double** matrix;
    matrix = (double**)malloc(sizeof(double*) * size_x);
    if (matrix == NULL) {
        *status = memory_allocation_fail;
        return NULL;
    }
    for (int i = 0; i < size_x; i ++) {
        double* row;
        row = (double*)malloc(sizeof(double) * size_y);
        if (row == NULL) {
            *status = memory_allocation_fail;
            return NULL;
        }
        for (int j = 0; j < size_y; j ++) {
//            когда флаг равен 1, мы заполняем матрицу нулями, нужно для флага b
            if (!flag) row[j] = A + (B - A) / RAND_MAX * rand();
            else row[j] = 0;
        }
        matrix[i] = row;
    }
    srand((unsigned int)(time(NULL) + rand()));
    return matrix;
}
 
void print_matrix(double** mat, int size_x, int size_y) {
    for (int i = 0; i < size_x; i ++) {
        for (int j = 0; j < size_y; j ++) {
            printf("%lf ", mat[i][j]);
        }
        printf("\n");
    }
}
 
void clean_memo_matrix(double** mat, int n) {
    for (int i = 0; i < n; i ++) {
        free(mat[i]);
        mat[i] = NULL;
    }
    free(mat);
}
 
void flag_a(Fails* status) {
    printf("Введите размеры желаемой матрицы (2 числа в диапозоне 1-10):\n");
    int row = -1;
    int column = -1;
    if ((scanf("%d", &row) == 1) && (row >= 1 && row <= 10) && (scanf("%d", &column) == 1) && (column >= 1 && column <= 10)) {
        double** matrix = create_matrix(status, row, column, 0);
        if (matrix == NULL) {
            return ;
        }
        printf("Сгенерированная матрица:\n");
        print_matrix(matrix, row, column);
        clean_memo_matrix(matrix, row);
    }
    else {
        *status = wrong_params;
    }
}
 
void flag_b(Fails* status, int is_flag_c) {
    printf("Введите размеры желаемой матрицы 1 (2 числа в диапозоне 1-10):\n");
    int row_1 = -1;
    int column_1 = -1;
    int row_2 = -1;
    int column_2 = -1;
    int flag_of_difference = 0;
    if ((scanf("%d", &row_1) == 1) && (row_1 >= 1 && row_1 <= 10) && (scanf("%d", &column_1) == 1) && (column_1 >= 1 && column_1 <= 10)) {
        printf("Введите размеры желаемой матрицы 2 (2 числа в диапозоне 1-10):\n");
        if ((scanf("%d", &row_2) == 1) && (row_2 >= 1 && row_2 <= 10) && (scanf("%d", &column_2) == 1) && (column_2 >= 1 && column_2 <= 10)) {
            if (!(column_1 == row_2)) {
                *status = wrong_params_mult;
                return ;
            }
            srand((unsigned int)(time(NULL)));
            double** matrix_1 = create_matrix(status, row_1, column_1, 0);
            double** matrix_2 = create_matrix(status, row_2, column_2, 0);
            double** matrix_out = create_matrix(status, row_1, column_2, 1);
            if (matrix_1 == NULL || matrix_out == NULL || matrix_2 == NULL) {
                return ;
            }
            printf("Сгенерированная матрица №1:\n");
            print_matrix(matrix_1, row_1, column_1);
            printf("Сгенерированная матрица №2:\n");
            print_matrix(matrix_2, row_2, column_2);
            printf("Результат умножения:\n");
            mult_matrix(matrix_1, matrix_2, matrix_out, row_1, column_2, row_2);
            print_matrix(matrix_out, row_1, column_2);
            if (is_flag_c) {
                if (row_1 == column_1) {
                    printf("Матрица 1 ");
                    flag_c(status, matrix_1, row_1);
                    flag_of_difference = 1;
                }
                if (row_2 == column_2) {
                    printf("Матрица 2 ");
                    flag_c(status, matrix_2, row_2);
                    flag_of_difference = 1;
                }
                if (row_1 == column_2) {
                    printf("Матрица после умножения ");
                    flag_c(status, matrix_out, column_2);
                    flag_of_difference = 1;
                }
                if (flag_of_difference == 0) {
                    *status = wrong_params_determ;
                    return ;
                }
                return ;
            }
            clean_memo_matrix(matrix_1, row_1);
            clean_memo_matrix(matrix_2, row_2);
            clean_memo_matrix(matrix_out, row_1);
        }
        else {
            *status = wrong_params;
            return ;
        }
    }
    else {
        *status = wrong_params;
        return ;
    }
}
 
void flag_c(Fails* status, double** matrix, int size) {
        double** matrix_1_1 = matrix;
        if (matrix_1_1 == NULL) {
            *status = memory_allocation_fail;
            return ;
        }
        printf("определитель = ");
        printf("%lf\n", gauss(matrix, matrix_1_1, size));
}
void mult_matrix(double** mat_1, double** mat_2, double** mat_out, int x, int y, int z) {
    for (int i = 0; i < x; i ++) {
        for (int j = 0; j < y; j ++) {
            for (int k = 0; k < z; k ++) {
                mat_out[i][j] += (mat_1[i][k] * mat_2[k][j]);
            }
        }
    }
}
 
double gauss(double** matrix, double** matrix_c, int size) {
    for (int i = 0; i < size; ++ i) {
        int string_max = i;
        for (int j = i + 1; j < size; ++ j) {
            if (fabs(matrix_c[j][i]) > fabs(matrix_c[string_max][i]))
                string_max = j; // находим строку с максимальным первым элементом
        }
        //Если в матрице нули или она состоит целиком из них:
        if (fabs(matrix_c[string_max][i]) < eps) {
            continue;
        }
        for (int k = 0; k < size; ++ k) { //меняем строки местами поэлементно
            swap(&matrix_c[i][k], &matrix_c[string_max][k]);
        }
        for (int j = i + 1; j < size; ++ j) { //вычетаем строку из других
            double q = - matrix_c[j][i] / matrix_c[i][i];
            for (int k = size - 1; k >= i; -- k) {
                matrix_c[j][k] += q * matrix_c[i][k];
            }
        }
    }
    double mult = 1.0;
    for (int i = 0; i < size; i ++) {
        mult *= matrix_c[i][i];
    }
    //print_matrix(matrix_c, size, size);
    return mult;
}
/* чистый флаг с, сам запрашивающий размер
void flag_c(Fails* status) {
    printf("Введите размер матрицы для вычисления определителя\n");
    int size = -1;
    if ((scanf("%d", &size) == 1) && (size >= 1 && size <= 10)) {
        double** matrix_1 = create_matrix(status, size, size, 0);
        double** matrix_1_1 = matrix_1;
        if (matrix_1 == NULL || matrix_1_1 == NULL) {
            *status = memory_allocation_fail;
            return ;
        }
        printf("Сгенерированная матрица:\n");
        print_matrix(matrix_1, size, size);
        printf("Ее определитель = ");
        printf("%lf\n", gauss(matrix_1, matrix_1_1, size));
    }
    else {
        *status = wrong_params;
        return ;
    }
}
*/
