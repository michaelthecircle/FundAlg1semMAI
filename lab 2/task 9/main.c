#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <locale.h>
#include <string.h>
#define max(a,b) (a>b)?(a):(b)
typedef enum Type_of_Fails {
    ok,
    wrong_s_s,
    memory_allocation_fail,
    wrong_n,
    wrong_input
}Fails;
 
long long len(char* massive) {
    long long len = 0;
    char* ptr = massive;
    while (*ptr != '\0') {
        len ++;
        ptr ++;
    }
    return len;
}
void input(Fails* status, int s_s, int n, ...);
char* summa(Fails* status, char* mas, int s_s, long long len_max, long long len_min, char* lex_max, char* lex_min);
int check(int lexem, int s_s);
char* reverse_massive(Fails* status, char* massive, long long len);
 
int main(void) {
    setlocale(LC_ALL, "Russian");
    Fails status;
    input(&status, 10 , 2, "100", "222222222222");
    switch(status) {
        case wrong_input:
            printf("Неверный ввод символов данной системы счисления\n");
            break;
        case wrong_s_s:
            printf("Неверно, введите систему счисления в диапозоне [2..36]\n");
            break;
        case wrong_n:
            printf("Неверное количество чисел\n");
            break;
        case memory_allocation_fail:
            printf("Ошибка выделения памяти\n");
            break;
        case ok:
            break;
    }
    return 0;
}
 
void input(Fails* status, int s_s, int n, ...) {
    if (s_s < 2 || s_s >= 36) {
        *status = wrong_s_s;
        return ;
    }
    if (n < 2) {
        *status = wrong_n;
        return ;
    }
    va_list factor;
    va_start(factor, n);
    char* slovo;
    char* slovo2;
    char* res = NULL;
    char* cur_res = NULL;
    long long len_max = 0;
    long long len_min = 0;
    long long len_slovo = 0;
    long long len_slovo_2 = 0;
    for (int i = 0; i < n - 1; i++) {
        if (i == 0) {
            slovo = va_arg(factor, char*);
        }
        else {
            slovo = res;
            //printf("%s\n", slovo);
        }
        slovo2 = va_arg(factor, char*);
        len_slovo = len(slovo);
        len_slovo_2 = len(slovo2);
        len_max = max(len_slovo, len_slovo_2);
        char* mas = NULL;
        if (len_slovo == len_max) {
            mas = (char*)malloc(len_slovo*(sizeof(char)));
            if (mas == NULL) {
                *status = memory_allocation_fail;
                return ;
            }
            res = summa(status, mas, s_s, len_slovo, len_slovo_2, slovo, slovo2);
            if (res == 0) {
                free(mas);
                return ;
            }
            //printf("%s\n", res);
            // free(mas);
            // mas = NULL;
            //memcpy();
        }
        else {
            mas = (char*)malloc(len_slovo_2*(sizeof(char)));
            if (mas == NULL) {
                *status = memory_allocation_fail;
                return ;
            }
            res = summa(status, mas, s_s, len_slovo_2, len_slovo, slovo2, slovo);
            if (res == 0) {
                free(mas);
                return ;
            }
            //printf("%s\n", res);
            // free(mas);
            // mas = NULL;
        }
        if (i == n - 2) {
            printf("%s\n", res);
            free(mas);
        }
    }
    *status = ok;
}
 
char* summa(Fails* status, char* mas, int s_s, long long len_max, long long len_min, char* lex_max, char* lex_min) {
    int tek_chislo = 0;
    int tek_chislo_2 = 0;
    int perenos = 0;
    for (long long i = len_max - 1, j = len_min - 1, o = 0; i >= 0; i--, j--, o++) {
        if (j < 0) {
            tek_chislo = check(lex_max[i], s_s);
            if (tek_chislo == -1) {
                *status = wrong_input;
                return 0;
            }
            tek_chislo += perenos;
            if ((tek_chislo) < s_s) {
                if (tek_chislo >= 10) {
                    mas[o] = tek_chislo + 55;
                }
                else {
                    mas[o] = tek_chislo + '0';
                }
                perenos = 0;
            }
            else {
                mas[o] = (tek_chislo) % s_s + '0';
                perenos = 1;
            }
        }
        else if (j > 0){
            tek_chislo = check(lex_max[i], s_s);;
            if (tek_chislo == -1) {
                *status = wrong_input;
                return 0;
            }
            tek_chislo += perenos;
            tek_chislo_2 = check(lex_min[j], s_s);
            if (tek_chislo_2 == -1) {
                *status = wrong_input;
                return 0;
            }
            tek_chislo += tek_chislo_2;
            perenos = 0;
            if ((tek_chislo) < s_s) {
                if (tek_chislo >= 10) {
                    mas[o] = tek_chislo + 55;
                }
                else {
                    mas[o] = tek_chislo + '0';
                }
            }
            else {
                mas[o] = (tek_chislo) % s_s + '0';
                perenos = 1;
            }
        }
        else {
            tek_chislo = check(lex_max[i], s_s);;
            if (tek_chislo == -1) {
                *status = wrong_input;
                return 0;
            }
            tek_chislo += perenos;
            tek_chislo_2 = check(lex_min[j], s_s);
            if (tek_chislo_2 == -1) {
                *status = wrong_input;
                return 0;
            }
            tek_chislo += tek_chislo_2;
            perenos = 0;
            if ((tek_chislo) < s_s) {
                if (tek_chislo >= 10) {
                    mas[o] = tek_chislo + 55;
                }
                else {
                    mas[o] = tek_chislo + '0';
                }
            }
            else {
                mas[o] = (tek_chislo) % s_s + '0';
                perenos = 1;
            }
        }
    }
    if (perenos == 1) {
        char* mas_realloc = (char*)realloc(mas, len_max*(sizeof(char)) + 1);
        if (mas_realloc == NULL) {
            *status = memory_allocation_fail;
            return 0;
        }
        mas = mas_realloc;
        mas[len_max] = '1';
    }
    char* ptr = mas + (long long)len_max + (long long)perenos - 1;
    long long leading_zeroes = 0;
    if (*ptr == '0') {
        while (*ptr == '0') {
            leading_zeroes ++;
            ptr --;
        }
    }
    char* mas_2 = (char*)realloc(mas, (len_max + (long long)perenos - leading_zeroes)*(sizeof(char)));
    if (mas_2 == NULL) {
        *status = memory_allocation_fail;
        return 0;
    }
    mas_2 = reverse_massive(status, mas_2, len_max + (long long)perenos - leading_zeroes);
    if (mas_2 == 0) {
        return 0;
    }
    return mas_2;
}
 
int check(int lexem, int s_s) {
    int chislo = 0;
    if (lexem >= 48 && lexem <= 57) {
        chislo = (lexem - '0');
        if (chislo >= s_s) {
            return -1;
        }
    }
    else if (lexem >= 65 && lexem <= 90) {
        chislo = (lexem - 55);
        if (chislo >= s_s) {
            return -1;
        }
    }
    else {
        return -1;
    }
    return chislo;
}
 
char* reverse_massive(Fails* status, char* massive, long long len) {
    char* duplicate = (char*)malloc(len * sizeof(char));
    if (duplicate == NULL) {
        *status = memory_allocation_fail;
        return 0;
    }
    char* ptr = massive + len - 1;
    for (unsigned long long i = 0; i < len; i ++) {
        duplicate[i] = *ptr;
        ptr --;
    }
    return duplicate;
}
