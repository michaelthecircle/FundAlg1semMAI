#include <stdio.h>
#include <stdarg.h>
#include <math.h>

double geom_proizv(int n, ...) {
    double proizv = 1;
    va_list factor;
    va_start(factor, n);
    for (int i = 0; i < n; i++) {
        proizv *= va_arg(factor, double);
    }
    va_end(factor);
    if (n == 1) {
        return -2;
    }
    else if ((proizv < 0) && (n % 2 == 0)) {
        return -1;
    }
    else {
        double rez = pow(proizv, (1.0 / n));
        return rez;
    }
}

double power(double a, int n) {
    if (n == 0) {
        return 1;
    }
    else if (n >= 1) {
        return a * power(a, n - 1);
    }
    else if (n <= 1) {
        return (1.0 / a) * power(a, n + 1);
    }
    return 0;
}

int main(void) {
    double res = geom_proizv(2, 9.0, 8.0);
    if (res == -1) {
        printf("Корень не определен\n");
    }
    else if (res == -2) {
        printf("Введено слишком мало аргументов для среднего геометрического\n");
    }
    else {
        printf("Среднее геометрическое: %.10lf\n", res);
    }
    printf("Возведение в степень: %.10lf\n", power(2, -3));
}
