#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n_a, n_b, *mas1, *mas2, *mas3;
    printf("Введите размер массива A: ");
    scanf("%d", &n_a);
    printf("Введите размер массива B: ");
    scanf("%d", &n_b);
    mas1 = malloc(n_a * sizeof(int));
    printf("Сгенерированный массив A: ");
    srand(time(NULL));
    for (int i = 0; i < n_a; i++) {
//           mas[i] = rand() % (B-A+1) + A //диапазон от A до B
        mas1[i] = rand() % 100;
        printf("%d ", mas1[i]);
    }
    printf("\n");
    mas2 = malloc(n_b * sizeof(int));
    printf("Сгенерированный массив B: ");
    for (int i = 0; i < n_b; i++) {
        mas2[i] = rand() % 100;
        printf("%d ", mas2[i]);
    }
    printf("\n");
    mas3 = malloc(n_a * sizeof(int));
    int k = n_b;
    for (int i = 0; i < n_a; i++) {
        if (k > 0) {
            mas3[i] = mas1[i] + mas2[i];
            k --;
        }
        else {
            if (mas2[i] != 0) {
                mas3[i] = mas1[i] + mas2[n_b-1];
            }
            else {
                mas3[i] = mas1[i] + 0;
            }
        }
    }
    printf("Сгенерированный массив C: ");
    for (int i = 0; i < n_a; i++) {
        printf("%d ", mas3[i]);
    }
    printf("\n");
    free(mas3);
    free(mas1);
    free(mas2);
    return 0;
}
