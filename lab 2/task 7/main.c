#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#define eps 0.00001

typedef struct spoint {
    double x, y;
}coordinates;

typedef enum ERRORS{
    memory_allocation_fail,
    ok
}ERROR;

bool isbigger(double first, double second) {
    bool flag = ((first - second) > eps)?true:false;
    return flag;
}
bool issmaller(double first, double second) {
    bool flag = ((first - second) < -(eps))?true:false;
    return flag;
}

bool vect(ERROR* error, int n, ...) {
    if (n < 3) {
        return false;
    }
    double min_x = DBL_MAX;
    double max_x = DBL_MIN;
    double min_y = DBL_MAX;
    double max_y = DBL_MIN;
    coordinates first_point;
    va_list factor;
    va_start(factor, n);
    coordinates *mas_p;
    mas_p = (coordinates*)malloc(n*(sizeof(coordinates)));
    if (mas_p == NULL) {
        *error = memory_allocation_fail;
        return false;
    }
    for (int i = 0; i < n; i++) {
        coordinates p;
        p.x = va_arg(factor, double);
        if (issmaller(p.x, min_x)) {
            min_x = p.x;
        }
        else if (isbigger(p.x, max_x)) {
            max_x = p.x;
        }
        p.y = va_arg(factor, double);
        if (issmaller(p.y, min_y)) {
            min_y = p.y;
        }
        else if (isbigger(p.y, max_y)) {
            max_y = p.y;
        }
        mas_p[i] = p;
    }
//   это сравнение необходимо для того чтобы учесть случай когда первая точка может быть крайней, связано это с невозомжностью корректного сравнения с мин и макс в цикле выше
    first_point = mas_p[0];
    if (issmaller(first_point.x, min_x)) {
        min_x = first_point.x;
    }
    else if (isbigger(first_point.x, max_x)) {
        max_x = first_point.x;
    }
    if (issmaller(first_point.y, min_y)) {
        min_y = first_point.y;
    }
    else if (isbigger(first_point.y, max_y)) {
        max_y = first_point.y;
    }
    for (int i = 0; i < n; i ++) {
        if (((isbigger(mas_p[i].x, min_x)) && (issmaller(mas_p[i].x, max_x))) && ((isbigger(mas_p[i].y, min_y) && (issmaller(mas_p[i].y, max_y))))) {
            free(mas_p);
            return false;
        }
    }
    free(mas_p);
    return true;
}
double polynom(int x, int n, ...) {
    if (n < 1) {
        return false;
    }
    double res = 0.0;
    va_list factor;
    va_start(factor, n);
    for (int i = 0; i <= n; i++) {
        res = res * x + va_arg(factor, double);
    }
    return res;
}

int main(void) {
    ERROR error;
    bool res = vect(&error, 4, 3.5, 4.9, 1.2, 2.0, 5.1, 2.8, 3.0, 0.0);
    if (res) {
        printf("Многоугольник выпуклый\n");
    }
    else {
        printf("Многоугольник не выпуклый\n");
    }
    double res_pol = polynom(-2, 3, 1.5, 2.5, 9.0, 1.0);
    if (!res_pol) {
        printf("Некорректный ввод полинома\n");
    }
    else {
        printf("Ответ: %lf\n", res_pol);
    }
    switch(error) {
        case memory_allocation_fail:
            printf("Ошибка выделения памяти\n");
            break;
        default:
            break;
    }
    return 0;
}

