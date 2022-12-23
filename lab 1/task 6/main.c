#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int power(unsigned a, unsigned long b) {
    int tek = 1;
    for (int i = 0; i < b; i++) {
        tek *= a;
    }
    return tek;
}
long long n_to_dec(int* str, int ss, unsigned long len_str) {
    int sum = 0;
//    printf("%d\n", ss);
    for (unsigned long i = len_str - 1, j = 0; i > 0; i--, j++) {
        sum += power(ss, j) * str[i];
//        sum += str[i];
//        printf("%d\n", sum);
    }
    sum += power(ss, len_str - 1) * str[0];
//    printf("%d\n", power(ss, len_str - 1));
    return sum;
}

int define_ss(char* str, int* new_str, unsigned long len_str) {
    unsigned tek_ss = 0;
    for (unsigned long i = 0; i < len_str; i ++) {
        if (!((str[i] < 48) || ((str[i] > 57) && (str[i] < 65)) || (str[i] > 90))) {
            if ((str[i] >= 48) && (str[i] <= 57)) {
                new_str[i] = str[i] - '0';
            }
            else if ((str[i] >= 65) && (str[i] <= 90)) {
                new_str[i] = str[i] - '0' - 7;
            }
            if (str[i] > tek_ss) {
                tek_ss = str[i];
            }
        }
        else {
            tek_ss = 200; //типо код ошибки
            free(new_str);
            break;
        }
    }
    return tek_ss;
}
int task(FILE* file, FILE* outfile) {
    char *mas = NULL;
    int buff = 100;
    mas = (char*)malloc(sizeof(char) * (buff + 1));
    if (mas == NULL) {
        return -1;
    }
    int tek_poz = 0;
    char symb;
    char *mas2;
    while ((symb = fgetc(file)) != EOF) {
        if (tek_poz < buff) {
            mas[tek_poz] = symb;
            tek_poz ++;
        }
        else {
            buff *= 2;
            mas2 = (char*)realloc(mas, sizeof(char) * (buff + 1));
            if (mas2 == NULL) {
                free(mas);
                return -1;
            }
            mas = mas2;
            mas[tek_poz] = symb;
            tek_poz ++;
        }
    }
    char *str;
    str = strtok(mas,"\n \t");
    int ss = 0;
    unsigned long len_str = 0;
    int *new_str = NULL;
    long long res = 0;
    while (str != NULL)
    {
        len_str = strlen(str);
        new_str = (int*)malloc(sizeof(int) * len_str);
        ss = define_ss(str, new_str, len_str) + 1;
        printf("%d\n", ss);
        if ((ss >= 49) && (ss <= 58)) {
            ss -= 48;
        }
        else if ((ss >= 65) && (ss <= 90)) {
            ss -= 55;
        }
        else if (ss == 201) {
            fprintf(outfile, "%s ", str);
            fprintf(outfile, "Невозможно определить систему счисления(неверный ввод)\n");
            return -2;
        }
        res = n_to_dec(new_str, ss, len_str);
        fprintf(outfile, "%s ", str);
        fprintf(outfile, "%d ", ss);
        fprintf(outfile, "%lld\n", res);
        free(new_str);
        str = strtok (NULL,"\n \t");
    }
    free(mas);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2){
        printf("Недостаточно аргументов\n");
        return -1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Невозможно открыть указанный файл\n");
        return -1;
    }
    FILE* outfile;
    const char* path = argv[1];
    char title[100] = "out_";
    strcat(title, path);
    outfile = fopen(title, "w");
    if (outfile == NULL) {
        printf("Выходной файл не создался\n");
        return -1;
    }
    int task_res = task(file, outfile);
    if (task_res == -1) {
        printf("Недостаточно памяти для создания массива чисел\n");
        return -1;
    }
    else if (task_res == -2) {
        printf("Неверный ввод\n");
        return -1;
    }
//    else if (task_res == -2) {
//        printf("Одного из заданных символов в системах счисления 1-36 не существует\n");
//        return -1;
//    }
    return 0;
}
