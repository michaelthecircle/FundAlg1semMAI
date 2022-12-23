#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define BUFFSIZE 100

long long n_to_dec(int* str, int ss, unsigned long len_str, int *flag);
int input(int system);
bool check_system(char* token, int system, unsigned long *len, int* str, int *flag);
void transfer(long long number, int base, unsigned long len);

int main(void) {
    int system = 0;
    if (scanf("%d", &system) == 1) {
        if (!(system >= 2 && system <= 36)) {
            printf("Неверный ввод\n");
            return -1;
        }
    }
    else {
        printf("Неверный ввод\n");
        return -1;
    }
    int check_input = input(system);
    if (check_input == -1) {
        printf("Некорректный ввод\n");
        return -1;
    }
    return 0;
}

int input(int system) {
    char res[BUFFSIZE];
    int tek_lex;
    long long max = LLONG_MIN;
    unsigned long len = 0;
    unsigned long len_max = 0;
    long long sum = 0;
    int* str = (int*)malloc(sizeof(int)*BUFFSIZE);
    int flag = 1; //флаг отрицательности
    while (scanf("%s", res) != EOF || (strcmp(res, "stop"))) {
        if (!strcmp(res, "stop")) {
            break;
        }
        tek_lex = check_system(res, system, &len, str, &flag);
        if (len > 10) {
            return -1;
        }
        if (tek_lex == true) {
            sum = n_to_dec(str, system, len, &flag);
            if (sum > max) {
                max = sum;
                len_max = len;
            }
        }
        else continue;
        len = 0;
        flag = 1;
    }
    if (max != LLONG_MIN) {
        printf("MAX CHISLO in decimal base = %lld\n", max);
        transfer(max, system, len_max);
        transfer(max, 9, len_max);
        transfer(max, 18, len_max);
        transfer(max, 27, len_max);
        transfer(max, 36, len_max);
    }
    return 0;
}

bool check_system(char* token, int system, unsigned long *len, int* str, int *flag) {
    int i = 0;
    if (*token == '-') {
        (*flag) *= -1;
        token ++;
    }
    while (*token != '\0') {
        if (*token >= 48 && *token <= 57) {
            *token -= '0';
            if (*token >= system){
                return false;
            }
            (*len)++;
            str[i] = *token;
        }
        else if (*token >= 65 && *token <= 90) {
            *token -= 55;
            if (*token >= system) {
                return false;
            }
            (*len)++;
            str[i] = *token;
        }
        else {
            return false;
        }
        token ++;
        i ++;
    }
    return true;
}

int power(unsigned a, unsigned long b) {
    int tek = 1;
    for (int i = 0; i < b; i++) {
        tek *= a;
    }
    return tek;
}

long long n_to_dec(int* str, int ss, unsigned long len_str, int* flag) {
    int sum = 0;
    for (unsigned long i = len_str - 1, j = 0; i > 0; i--, j++) {
        sum += power(ss, j) * str[i];
    }
    sum += power(ss, len_str - 1) * str[0];
    return sum * (*flag);
}

void transfer(long long number, int base, unsigned long len) {
//    buffer for result
    if (number == 0) {
        printf("RESULT in %d base: %s\n", base, "0");
        return ;
    }
    char buff[BUFFSIZE];
    char *ptr = buff + BUFFSIZE - 1;
    *ptr-- = '\0';
    int temp = 0;
    char sign = 0;
    if (number < 0) {
        sign = '-';
        number = llabs(number);
    }
    while (number) {
        temp = number % base;
        if (temp > 9) {
            *ptr-- = temp + 55;
        }
        else {
            *ptr-- = temp + 48;
        }
        number /= base;
    }
    printf("RESULT in %d base: %c%s\n", base, sign, ptr + 1);
}
