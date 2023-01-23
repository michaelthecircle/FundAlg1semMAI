#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef enum Fails {
    ok,
    memory_allocation_fail,
    wrong_files
}Fails;


long long input(char** sublex, Fails* status);
int task(Fails* status, char* sublex, long long len_sublex, int count, ...);
int string_read(Fails* status, FILE* file, char* sublex, long long len_sublex);
long long search(char* sublex, long long len_sublex, char* cur_string, long long len_cur, long long number_string);
void printer(int flag, long long number_string, long long index);

int main(void) {
    Fails status;
    char* sublex = NULL;
    long long len_sublex = 0;
    if ((len_sublex = input(&sublex, &status)) != -1) {
//        printf("%lu\n", strlen(sublex));
        task(&status, sublex, len_sublex, 2, "file_1.txt", "file_2.txt");
    }
    free(sublex);
    switch(status) {
        case memory_allocation_fail:
            printf("Ошибка выделения памяти\n");
            break;
        case ok:
            break;
        case wrong_files:
            break;
    }
    return 0;
}

long long input(char** s_sublex, Fails* status) {
    printf("Введите подстроку:");
    char c;
    int SIZE = 10;
    char* sublex = NULL;
    sublex = (char*)malloc(sizeof(char) * SIZE);
    if (sublex == NULL) {
        *status = memory_allocation_fail;
        return -1;
    }
    long long cur_index_sublex = 0;
    while ((c = getchar()) != '\n') {
        if (cur_index_sublex < SIZE) {
            sublex[cur_index_sublex] = c;
        }
        else {
            SIZE *= 2;
            char* realloc_sublex = (char*)realloc(sublex, sizeof(char) * SIZE);
            if (realloc_sublex == NULL) {
                *status = memory_allocation_fail;
                return -1;
            }
            sublex = realloc_sublex;
            sublex[cur_index_sublex] = c;
            
        }
        cur_index_sublex ++;
    }
    *status = ok;
    *s_sublex = sublex;
    return cur_index_sublex ++;
}

int task(Fails* status, char* sublex, long long len_sublex, int count, ...) {
    int wrong_files = 0;
    int res = 0;
    FILE* fp;
    va_list n;
    va_start(n, count);
    for(int i = 0; i < count; ++i){
        char* file_name = va_arg(n, char*);
        fp = fopen(file_name, "r");
        if(fp == NULL){
            wrong_files ++;
            continue;
        }
        printf("в файле %s", file_name);
        if (len_sublex == 0) {
            printer(2, 0, 0);
            res = 1;
        }
        else res = string_read(status, fp, sublex, len_sublex);
        if (res == -1) {
            return -1;
        }
        else if (res != 1){
            printf("\nнет подстроки!");
        }
        fclose(fp);
        printf("\n");
    }
    va_end(n);
    if (wrong_files != 0) {
        printf("\nНе удалось прочитать %d файлов\n", wrong_files);
        *status = wrong_files;
    }
    return 0;
}

int string_read(Fails* status, FILE* file, char* sublex, long long len_sublex) {
    char c = '\0';
    char* cur_string = NULL;
    char* realloc_string = NULL;
    long long res_search = 0;
    long long number_string = 1;
    int SIZE = 10;
    cur_string = (char*)malloc(sizeof(char) * SIZE);
    if (cur_string == NULL) {
        *status = memory_allocation_fail;
        return -1;
    }
    long long cur_index = 0;
    while (c != EOF) {
        if (cur_index < SIZE) {
            cur_string[cur_index] = c;
        }
        else {
            SIZE *= 2;
            realloc_string = (char*)realloc(cur_string, sizeof(char) * SIZE);
            if (realloc_string == NULL) {
                *status = memory_allocation_fail;
                return -1;
            }
            cur_string = realloc_string;
            cur_string[cur_index] = c;
        }
        c = fgetc(file);
        if ((c == '\n')  || (c == EOF)){
            res_search = search(sublex, len_sublex , cur_string + 1, cur_index, number_string);
            if (res_search == -1) {
                *status = memory_allocation_fail;
                return -1;
            }
            cur_index = - 1;
            free(cur_string);
            if (res_search == -2) {
                return 2;
            }
            SIZE = 10;
            cur_string = NULL;
            cur_string = (char*)malloc(sizeof(char) * SIZE);
            if (cur_string == NULL) {
                *status = memory_allocation_fail;
                return -1;
            }
            number_string ++;
        }
        cur_index ++;
    }
    if (res_search != 0) {
        free(cur_string);
        return 1;
    }
    return 0;
}

long long search(char* sublex, long long len_sublex, char* cur_string, long long len_cur, long long number_string) {
    int flag = 1;
    if (len_sublex > len_cur) {
        return -2;
    }
    if (len_sublex == 0) {
        return -2;
    }
// Если длина лексемы для поиска = 1, можно посчитать быстрее без нового массива, но чтобы показать что программа работает корректно для длины 1, то оставлю как есть
//    if (len_sublex == 1) {
//        for (long long i = 0; i < len_cur; i ++) {
//            if (cur_string[i] == *sublex) {
//                printer(flag, number_string, i);
//                flag = 0;
//            }
//        }
//        if (flag == 0) {
//            return 1;
//        }
//        else {
//            return 0;
//        }
//    }
    char* copy_area = (char*)malloc(sizeof(char) * len_sublex + 1);
    if (copy_area == NULL) {
        return -1;
    }
    for (long long i = 0; i <= len_cur - len_sublex; i ++) {
        if (cur_string[i] == sublex[0]) {
            memcpy(copy_area, cur_string + i, (size_t)len_sublex);
            if (!strcmp(copy_area, sublex)) {
                printer(flag, number_string, i);
                flag = 0;
            }
        }
    }
    free(copy_area);
    if (flag == 0) {
        return 1;
    }
    return 0;
}

void printer(int flag, long long number_string, long long index) {
    if (flag == 1) {
        printf("\nВ строке №%lld подстрока с индексом(ами) %lld ", number_string, index);
    }
    else if (flag == 0){
        printf("%lld ", index);
    }
    else {
        printf("\nпустота содержится как подстрока");
    }
}
