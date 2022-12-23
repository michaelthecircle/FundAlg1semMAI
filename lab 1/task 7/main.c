#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define size 20
#define B 100
#define A -100


int main(void) {
//    поскольку массив фиксированного размера, пусть этот размер будет 20
    int *mas = NULL;
    mas = (int*)malloc(sizeof(int) * size);
    if (mas == NULL) {
        printf("Ошибка памяти\n");
        return -1;
    }
    printf("Сгенерированный массив до: ");
    srand(time(NULL));
    int min = INT_MAX;
    int max = INT_MIN;
    int ind_min = 0;
    int ind_max = 0;
    for (int i = 0; i < size; i++) {
        mas[i] = rand() % (B - (A + 1)) + A;
        if (mas[i] < min) {
            min = mas[i];
            ind_min = i;
        }
        else if (mas[i] > max) {
            max = mas[i];
            ind_max = i;
        }
        printf("%d ", mas[i]);
    }
    printf("\n");
    printf("Минимальный элемент: %d\n", min);
    printf("Максимальный элемент: %d\n", max);
    mas[ind_max] = min;
    mas[ind_min] = max;
    printf("Сгенерированный массив после: ");
    for (int i = 0; i < size; i ++) {
        printf("%d ", mas[i]);
    }
    printf("\n");
    free(mas);
    return 0;
}
