#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef METOD_SORT
#define sort
#endif

void flag_a(FILE* file, int* mas, int len);
void flag_b(FILE* file, int* mas, int len);
//int flag_c(FILE* file, int* mas, int len, int index, int decode);
void flag_c(FILE* file, int* mas, int len, int index);
void flag_d(FILE* file, int* mas, int index);
//int flag_e(FILE* file, int* mas, int len, int index, int decode);
void flag_e(FILE* file, int* mas, int len, int index);
int comp(const int *, const int *);
//int read_from_file(int* mas, FILE* file, int* len);

int max(a,b) {
    return a > b ? a : b;
}
int min(a,b) {
    return a < b ? a : b;
}
int reader(FILE* file, int* mas){
    char symb;
    int flag = 0; //показывает что число началось(1) или закончилось (0)
    int flag_non_dig = 0; //показывает что в данной лексеме есть буквы
    int number = 0;
    int tek_mas = 0; //порядок массива
    int flag_neg = 1; //отрицательное число
    while((symb = fgetc(file)) != EOF) {
        if (symb == '-') {
            if (flag_neg == -1) {
                flag_non_dig = 1;
            }
            else {
                flag_neg = -1;
                continue;
            }
        }
        if (symb >= '0' && symb <= '9') {
            if (flag_non_dig) {
                continue;
            }
            number *= 10;
            flag = 1;
            number += symb - '0';
        }
        else {
            if (symb == '\n' || symb == '\t' || symb == ' ') {
                flag_non_dig = 0;
            }
            else {
                flag_non_dig = 1;
            }
            if (flag) {
                if (tek_mas == 128) {
                    return -1;
                }
                if (flag_non_dig == 0) {
                    mas[tek_mas] = number * flag_neg;
                    tek_mas ++;
                }
            }
            flag_neg = 1;
            number = 0;
            flag = 0;
        }
    }
    if (flag) { //провека если число закончилось EOF'ом
        mas[tek_mas] = number * flag_neg;
        tek_mas += 1;
    }
    return tek_mas;
}

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Неверный ввод!\nПРИМЕР ПРАВИЛЬНОГО - ./task file.txt flag\n");
        return -1;
    }
    const char* path = argv[1];
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Невозомжно открыть указанный файл\n");
        return -2;
    }
    char title[100] = "out_";
    strcat(title, path);
    FILE* outfile = fopen(title, "w");
    if (outfile == NULL) {
        printf("Невозомжно создать еще один файл\n");
        return -2;
    }
    int mas[128];
//    int decode = -1;
    int res_read = -100;
    char flag = *argv[2];
        res_read = reader(file, mas);
        if (res_read == 1) {
            printf("Опереция не имеет смысла, так как введено 1 число\n");
            return -3;
        }
        else if (res_read == -1) {
            printf("Количество чисел больше 128!\n");
            return -3;
        }
        else if (res_read == 0) {
            printf("Не введено ни одно число\n");
            return -3;
        }
//    }
    if (flag == 'a') {
        flag_a(outfile, mas, res_read);
    }
    else if (flag == 'b') {
        flag_b(outfile, mas, res_read);
    }
    else if (flag == 'c') {
        int index = 0;
        printf("Введите индекс нужного элемента: ");
        if (scanf("%d", &index) != 1) {
            printf("Неверный ввод индекса\n");
            return -4;
        }
        if (index >= res_read || index < 0) {
            printf("Элемента с таким индексом не существует\n");
            return -4;
        }
        if (index < 0) {
            printf("Программа не предусмотрена на работу с отрицательными индексами\n");
            return -4;
        }
//        int flag_res = flag_c(outfile, mas, res_read, index, decode);
        flag_c(outfile, mas, res_read, index);
//        if (flag_res == -1) {
//            printf("Невозможно создать файл с кешированным отсортированным массивом\n");
//            return -5;
//        }
    }
    else if (flag == 'd') {
        int index = 0;
        printf("Введите индекс нужного элемента: ");
        if (scanf("%d", &index) != 1) {
            printf("Неверный ввод индекса\n");
            return -4;
        }
        if (index >= res_read || index < 0) {
            printf("Элемента с таким индексом не существует\n");
            return -4;
        }
        if (index < 0) {
            printf("Программа не предусмотрена на работу с отрицательными индексами\n");
            return -4;
        }
        flag_d(outfile, mas, index);
    }
    else if (flag == 'e') {
        int index = 0;
        printf("Введите индекс нужного элемента: ");
        if (scanf("%d", &index) != 1) {
            printf("Неверный ввод индекса\n");
            return -4;
        }
        if (index >= res_read || index < 0) {
            printf("Элемента с таким индексом не существует\n");
            return -4;
        }
        if (index < 0) {
            printf("Программа не предусмотрена на работу с отрицательными индексами\n");
            return -4;
        }
//        int flag_res = flag_e(outfile, mas, res_read, index, decode);
        flag_e(outfile, mas, res_read, index);
//        if (flag_res == -1) {
//            printf("Невозможно создать файл с кешированным отсортированным массивом\n");
//            return -5;
//        }
    }
    else {
        printf("Неверный флаг\n");
        return -8;
    }
    fclose(file);
    fclose(outfile);
    printf("SUCCESS\n");
    return 0;
}

void flag_a(FILE* file, int* mas, int len) {
    for (int i = 0; i < len; i += 2) {
        fprintf(file, "%d ", mas[i]);
    }
}

void flag_b(FILE* file, int* mas, int len) {
    for (int i = 0; i < len; i ++) {
        if ((mas[i] & 1) == 0) {
            fprintf(file, "%d ", mas[i]);
        }
    }
}

//int flag_c(FILE* file, int* mas, int len, int index, int decode) {
void flag_c(FILE* file, int* mas, int len, int index) {
    int comparable_number = mas[index];
    int max_far_number = 0;
    int max_diff = 0;
    if (len == 2) {
        if (index == 1) fprintf(file, "%d\n", mas[0]);
        else fprintf(file, "%d\n", mas[1]);
        return ;
    }
    
#ifdef sort
//    if (decode != 0) {
//        qsort(mas, len, sizeof (int), (int(*) (const void *, const void *)) comp);
//        FILE* cash_file = fopen("SORTED_MAS.txt", "w");
//        if (cash_file == NULL) {
//            return -1;
//        }
//        fprintf(cash_file, "%d\n", len);
//        for (int i = 0; i < len; i ++) {
//            fprintf(cash_file, "%d ", mas[i]);
//        }
//        fclose(cash_file);
//    }
    qsort(mas, len, sizeof (int), (int(*) (const void *, const void *)) comp);
    int comp_left = abs(comparable_number - mas[0]);
    int comp_right = abs(comparable_number - mas[len - 1]);
    max_far_number = (comp_left > comp_right) ? mas[0] : mas[len - 1];
    fprintf(file, "%d\n", max_far_number);
#else
    for (int i = 0; i < len; i ++) {
        if (i != index) {
            if (max(mas[i], comparable_number) - min(mas[i], comparable_number) > max_diff) {
                max_diff = max(mas[i], comparable_number) - min(mas[i], comparable_number);
                max_far_number = mas[i];
            }
        }
    }
    fprintf(file, "%d\n", max_far_number);
#endif
//    return 0;
}
int comp (const int *i, const int *j) {
    return *i - *j;
}

//int read_from_file(int* mas, FILE* file, int* len) {
//    if (fscanf(file, "%d", len) == 1) {
//        int i = 0;
//        for (i = 0; i < *len; i ++) {
//            if (fscanf(file, "%d", &mas[i]) == 1) continue;
//            else return -1;
//        }
//        if (fscanf(file, "%d", &mas[i+1]) == 1) {
//            return -1;
//        }
//    }
//    else return -1;
//    return 0;
//}

void flag_d(FILE* file, int* mas, int index) {
    if (index == 0) {
        fprintf(file, "");
        return ;
    }
    long long sum = 0;
    for (int i = 0; i < index; i ++) {
        sum += mas[i];
    }
    fprintf(file, "%lld", sum);
}

//int flag_e(FILE* file, int* mas, int len, int index, int decode) {
void flag_e(FILE* file, int* mas, int len, int index) {
    int comparable_number = mas[index];
    long long sum = 0;
    int j = 0;
#ifdef sort
//    if (decode != 0) {
//        qsort(mas, len, sizeof (int), (int(*) (const void *, const void *)) comp);
//        FILE* cash_file = fopen("SORTED_MAS.txt", "w");
//        if (cash_file == NULL) {
//            return -1;
//        }
//        fprintf(cash_file, "%d\n", len);
//        for (int i = 0; i < len; i ++) {
//            fprintf(cash_file, "%d ", mas[i]);
//        }
//        fclose(cash_file);
//    }
    qsort(mas, len, sizeof (int), (int(*) (const void *, const void *)) comp);
    while (mas[j] != comparable_number) {
        sum += mas[j];
        j ++;
    }
    fprintf(file, "%lld\n", sum);
#else
    for (int i = 0; i < len; i ++) {
        if (mas[i] < comparable_number) {
            sum += mas[i];
        }
    }
    fprintf(file, "%lld\n", sum);
//    for (int i = 0; i < len; i ++) {
//        if (i != index) {
//            if (max(mas[i], comparable_number) - min(mas[i], comparable_number) > max_diff) {
//                max_diff = max(mas[i], comparable_number) - min(mas[i], comparable_number);
//                max_far_number = mas[i];
//            }
//        }
//    }
//    fprintf(file, "%d\n", max_far_number);
#endif
//    return 0;
}
