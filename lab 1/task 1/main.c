#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
void func_h(int num) { //функция выводит кратные числа в диапозоне 1 - 100
    int* arr = (int*)malloc(sizeof(int) * 100);
    if (arr == NULL) {
        printf("Ошибка выделения памяти\n");
        return ;
    }
    int j = 0; //переменная для порядка массива
    for (int i = 1; i <= 100; i++) {
        if (num % i == 0) {
            arr[j] = i;
            j++;
        }
    }
//    printf("количество кратных чисел = %d\n",j);
    int* arr2;
    arr2 = realloc(arr, sizeof(int) * j);
    if (arr2 == NULL) {
        printf("Невозомжно выделить память\n");
        return ;
    }
    arr = arr2;
    if (arr == NULL) {
        printf("Кратных чисел в диапозоне 1 - 100 нет\n");
    }
    else {
        for (int i = 0; i < j; i++) {
            printf("%d\n", arr[i]);
        }
    }
    free(arr);
}

void prime(int num){
    if (num < 0) {
        printf("Отрицательные числа не простые и не составные\n");
        return ;
    }
    else if (num == 0) {
        printf("Ноль не простое и не составное число\n");
        return ;
    }
    for(int i = 2; i <= sqrt(num); i++) {
        if(num % i == 0) {
            printf("Число составное\n");
            return ;
        }
    }
    printf("Число простое\n");
    return ;
}

void digits(int num) {
    int flag = 0;
    if (num == 0) {
        printf("%d\n", num);
        return ;
    }
    else if (num < 0) {
        flag = 1;
        num *= -1;
    }
    int k = num;
    int m = 0;
    while (k != 0) {
        k = k / 10;
        m ++;
    }
    int* arr = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        arr[i] = num % 10;
        num /= 10;
    }
    if (flag == 1) {
        printf("- ");
    }
    for (int i = m - 1; i >= 0; i--) {
        printf("%d  ",arr[i]);
    }
    printf("\n");
}
long long int binpow (int a, int n)
{
    long long int res = 1;
    while (n)
    {
        if (n & 1) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

void power(int num) {
    for(int i = 1; i <= 10; i++) {
        for(int j = 1; j <= num; j++) {
            printf("%lld ", binpow(i, j));
        }
        printf("\n");
    }
}

void sum_digit(int num) {
    int sum = 0;
    for (int i = 1; i <= num; i++) {
        sum += i;
    }
    printf("%d\n", sum);
}

long long static int fact (int num)
{
  return (num < 2) ? 1 : num * fact (num - 1);
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Некорректный ввод\n");
        return -1;
    }
    
    char symb = argv[2][0];
    if (!(symb == '-' || symb == '/')) {
        printf("Неправильно введен флаг\n");
        return -1;
    }
    char flag = argv[2][1];
    int number = svoe_atoi(argv[1]);
    if (number < 0) {
        printf("Вводимое число должно быть положительным\n");
        return -1;
    }
    printf("ИНСТРУКЦИЯ:\n");
    printf("./task число флаг\n");
//    printf("%d\n", number);
    if (flag == 'h') {
        if (number == 0) {
            printf("Кратных чисел нет\n");
            return 0;
        }
        func_h(number);
        return 0;
    }
    else if (flag == 'p') {
        prime(number);
        return 0;
    }
    else if (flag == 's') {
        digits(number);
        return 0;
    }
    else if (flag == 'e') {
        if ((number < 1) || (number > 10)) {
            printf("Некорректно введено число для данного флага\n");
            return 0;
        }
        power(number);
        return 0;
    }
    else if (flag == 'a') {
        if (number < 1) {
            printf("Некорректно введены данные\n");
            return 0;
        }
        sum_digit(number);
        return 0;
    }
    else if (flag == 'f') {
        if (number < 0) {
            printf("Некорректно введены данные\n");
            return 0;
        }
        else if (number == 0) {
            printf("1\n");
            return 0;
        }
        printf("%lld\n", fact(number));
        return 0;
    }
    return 0;
}
