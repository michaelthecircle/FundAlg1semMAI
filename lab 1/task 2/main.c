#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define eps 0.00001

void equation(double par1, double par2, double par3);

double power(int a, int b) {
    int tek = 1;
    for (int i = 0; i < b; i++) {
        tek *= a;
    }
    return tek;
}

int svoe_atoi(char* str) {
    int znak = 1;
    if(*str == '-'){
        znak = -1;
        str ++;
    }
    int num = 0;
    while(*str){
        num=((*str)-'0') + num * 10;
        str ++;
    }
    return znak * num;
}

double svoe_atof(char* str) {
    int znak = 1;
    int num = 0;
    int flag = 0;
    int pow = 0;
    if (*str == '-') {
        znak = -1;
        str ++;
    }
    while (*str != '\0') {
        if (flag) {
            pow ++;
        }
        if ((*str == ',') || (*str == '.')) {
            str ++;
            flag = 1;
        }
        else {
            num = num * 10 + (*str - '0');
            str ++;
        }
    }
    return znak * num / power(10, pow);
}

void eq(double par1, double par2, double par3) {
    equation(par1, par2, par3);
    equation(par2, par1, par3);
    equation(par3, par1, par2);
    equation(par3, par2, par1);
    equation(par1, par3, par2);
    equation(par2, par3, par1);
}
void equation(double par1, double par2, double par3) {
    double discriminant = 0.0;
    double x1 = 0.0;
    double x2 = 0.0;
    printf("Для параметров %f %f %f:\n", par1, par2, par3);
    if (fabs(par1 - 0) < eps) {
        if (fabs(par2 - 0) < eps) {
            printf("Некорректно введены данные\n");
            return ;
        }
        x1 = (-par3) / (par2);
        if (fabs(x1 - 0) < eps) {
            x1 = 0;
            printf("x = %f\n", x1);
            return;
        }
        else {
            printf("x = %f\n", x1);
        }
        return ;
    }
    discriminant = par2 * par2 - 4 * (par1 * par3);
    if (discriminant < -eps) {
        printf("Действительных корней нет\n");
        return ;
    }
    else if (!abs((discriminant - 0) < eps)) {
        x1 = ((-par2) + sqrt(discriminant)) / (2 * par1);
        x2 = ((-par2) - sqrt(discriminant)) / (2 * par1);
        printf("x1 = %f ", x1);
        printf("x2 = %f\n", x2);
        return ;
    }
    else {
        x1 = ((-par2) + sqrt(discriminant)) / (2 * par1);
        printf("x1, x2 = %f\n", x1);
        return ;
    }
}

void multiplicity(int par1, int par2) {
    if (par1 == 0 || par2 == 0) {
        printf("Некорректно введены данные\n");
        return ;
    }
    if (par1 % par2 == 0) {
        printf("Первое число кратно второму\n");
        return ;
    }
    else {
        printf("Первое число не кратно второму\n");
        return ;
    }
}

void triangle(int par1, int par2, int par3) {
    if (par1 <= 0 || par2 <= 0 || par3 <= 0) {
        printf("Некорректно введены данные\n");
        return ;
    }
    if (par1 < par2) {
        if (par2 < par3) {
            if (par1 * par1 + par2 * par2 == par3 * par3) {
                printf("Могут быть сторонами прямоугольного треугольника\n");
                return ;
            }
            else {
                printf("Не могут быть сторонами прямоугольного треугольника\n");
                return ;
            }
        }
        else {
            if (par1 * par1 + par3 * par3 == par2 * par2) {
                printf("Могут быть сторонами прямоугольного треугольника\n");
                return ;
            }
            else {
                printf("Не могут быть сторонами прямоугольного треугольника\n");
                return ;
            }
        }
    }
    else if (par1 > par2) {
        if (par1 < par3) {
            if (par1 * par1 + par2 * par2 == par3 * par3) {
                printf("Могут быть сторонами прямоугольного треугольника\n");
                return ;
            }
            else {
                printf("Не могут быть сторонами прямоугольного треугольника\n");
                return ;
            }
        }
        else {
            if (par3 * par3 + par2 * par2 == par1 * par1) {
                printf("Могут быть сторонами прямоугольного треугольника\n");
                return ;
            }
            else {
                printf("Не могут быть сторонами прямоугольного треугольника\n");
                return ;
            }
        }
    }
    printf("Не могут быть сторонами прямоугольного треугольника\n");
    
}

int main(int argc, char * argv[]) {
//    Введенные числа для флага q будут типа double
    printf("Пример ввода: ./task -q 2 3 4\n");
    printf("Пример ввода: ./task -m 10 1\n");
    printf("Пример ввода: ./task -t 2 3 4\n");
    char symb = argv[1][0];
    if (!(symb == '-' || symb == '/')) {
        printf("Некорректно введен флаг\n");
        return 1;
    }
    char flag = argv[1][1];
    if (((argc < 5) || (argc > 5)) && ((flag == 'q') || (flag == 't'))) {
        printf("Некорректно введены данные\n");
        return 0;
    }
    if (((argc < 4) || (argc > 4)) && (flag == 'm')) {
        printf("Некорректно введены данные\n");
        return 0;
    }
    if (flag == 'q') {
        eq(svoe_atof(argv[2]), svoe_atof(argv[3]), svoe_atof(argv[4]));
    }
    else if (flag == 'm') {
        multiplicity(svoe_atoi(argv[2]), svoe_atoi(argv[3]));
    }
    else if (flag == 't') {
        triangle(svoe_atoi(argv[2]), svoe_atoi(argv[3]), svoe_atoi(argv[4]));
    }
    return 0;
}
