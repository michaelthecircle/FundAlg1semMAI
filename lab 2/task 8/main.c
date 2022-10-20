#include <stdio.h>
#include <math.h>
#include <float.h>
#include <locale.h>

double Function(double x) {
    return sqrt(1 - x) - tan(x);
}

double dichotomy(double a, double b, double(*form)(double x), double eps)
{
    double x = 0.0;
    while (fabs(a - b) > eps) {
        x = (a + b) / 2.0;
        if (form(a) * form(x) > eps) {
            a = x;
        } else {
            b = x;
        }
    }
    return x;
}
int main(void)
{
    double eps = 0.0;
    double a = 0.0;
    double b = 0.0;
    printf("Введите нижнюю границу отрезка: ");
    scanf("%lf", &a);
    printf("Введите верхнюю границу отрезка: ");
    scanf("%lf", &b);
    if (a > b) {
        printf("Некорректный ввод данных\n");
        return 0;
    }
    printf("Введите эпсилон: ");
    scanf("%lf", &eps);
    printf("Корень уравнения: %f\n", dichotomy(a, b, Function, eps));
    return 0;
}
