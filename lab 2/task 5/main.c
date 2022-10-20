#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

int not_in_array(int val, int* mas, int size){
    for(int i = 0; i < size; i++){
        if(mas[i] == val) {
            return 0;
        }
    }
    return 1;
}

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main() {
    int n_a, *mas1, *mas2, a, b;
    int max = INT_MIN;
    int min = INT_MAX;
    int index_max = 0;
    int index_min = 0;
    printf("Введите размер массива: ");
    scanf("%d", &n_a);
    printf("Введите диапозон генерации\n");
    printf("Первое число: ");
    scanf("%d", &a);
    printf("Второе число: ");
    scanf("%d", &b);
    if (a > b) {
        printf("Некорректно введены данные\n");
               return 0;
    }
    mas1 = malloc(n_a * sizeof(int));
    if (mas1 == NULL) {
        printf("Память не выделилась\n");
        return 0;
    }
    printf("Сгенерированный массив: ");
    srand(time(NULL));
    for (int i = 0; i < n_a; i++) {
        mas1[i] = rand() % (b-a+1) + a;
        printf("%d ", mas1[i]);
    }
    printf("\n");
    printf("(change)Желаете поменять максимальный элемент с минимальным\n(create)создать массив с уникальными элементами?\nНапишите 'change' или 'create': ");
    char answer[7];
    scanf("%s", answer);
    mas2 = (int*)malloc(n_a * sizeof(int));
    if (mas2 == NULL) {
        printf("Память не выделилась\n");
        return 0;
    }
    if (!strcmp(answer, "change")) {
        for (int i = 0; i < n_a; i++) {
            if (mas1[i] > max) {
                max = mas1[i];
                index_max = i;
            }
            if (mas1[i] < min) {
                min = mas1[i];
                index_min = i;
            }
        }
        swap((mas1 + index_min),(mas1 + index_max));
        for (int i = 0; i < n_a; i++) {
            printf("%d ", mas1[i]);
        }
    }
    int tek_poz = 0;
    int *tmp = NULL;
    if(!strcmp(answer, "create")) {
        for (int i = 0; i < n_a; i++) {
            if (not_in_array(mas1[i], mas2, n_a)) {
//                printf("%d\n", i);
//                printf("%d ", mas1[i]);
                mas2[tek_poz] = mas1[i];
                tek_poz ++;
            }
        }
//        printf("%d ", tek_poz);
        if (!(tmp = (int*)realloc(mas2, sizeof(int) * tek_poz))) {
            free(mas2);
            printf("Память не выделилась\n");
            return 0;
        }
        else {
            mas2 = tmp;
        }
//        printf("длина mas2 %d\n", sizeof((mas2)+1));
        for (int i = 0; i < tek_poz; i++) {
            printf("%d ", mas2[i]);
        }
    }
    printf("\n");
    free(mas1);
    free(mas2);
    return 0;
}
