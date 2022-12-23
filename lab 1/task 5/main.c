#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void write_file(char* str, FILE* outfile, unsigned int fail) {
    FILE *file = fopen(str, "r");
    if (file == NULL) {
        printf("Указанный по порядку файл №%u не существует\n", fail);
        return ;
    }
    char symb;
    while ((symb = fgetc(file)) != EOF) {
        fprintf(outfile, "%c", symb);
    }
}
void flag_fi(FILE* file, FILE* outfile) {
    char *mas = NULL;
    int buff = 100;
    mas = (char*)malloc(sizeof(char) * (buff + 1));
    if (mas == NULL) {
        printf("Массив не создался\n");
    }
    int tek_poz = 0;
    char symb;
    char* mas2;
    while ((symb = fgetc(file)) != EOF) {
        if (tek_poz < buff) {
            mas[tek_poz] = symb;
            tek_poz ++;
        }
        else {
            buff *= 2;
            mas2 = (char*)realloc(mas, sizeof(char) * (buff + 1));
            if (mas2 == NULL) {
                printf("Ошибка памяти\n");
                return ;
            }
            mas = mas2;
            mas[tek_poz] = symb;
            tek_poz ++;
        }
    }
    char *str;
    unsigned int fail = 1;
    str = strtok (mas,"\n");
    while (str != NULL)
    {
        write_file(str, outfile, fail);
        fail++;
        str = strtok (NULL,"\n");
    }
    if (mas) {
        free(mas);
    }
}

void flag_cin(FILE* outfile, char* name) {
    char *mas = NULL;
    int buff = 100;
    mas = (char*)malloc(sizeof(char) * (buff + 1));
    if (mas == NULL) {
        printf("Массив не создался\n");
    }
    int tek_poz = 0;
    char symb;
    char *mas2;
    while ((symb = getchar()) != EOF) {
        if (tek_poz < buff) {
            mas[tek_poz] = symb;
            tek_poz ++;
        }
        else {
            buff *= 2;
            mas2 = (char*)realloc(mas, sizeof(char) * (buff + 1));
            if (mas2 == NULL) {
                printf("Ошибка памяти\n");
                free(mas);
                return ;
            }
            mas[tek_poz] = symb;
            tek_poz ++;
        }
    }
    char *str;
    unsigned int fail = 1;
    str = strtok (mas,"\n");
    while (str != NULL)
    {
        if (!strcmp(str, name)) {
            printf("Ошибка! переименнуйте файл file_output.txt(данные из него не были обработаны)\n");
        }
        write_file(str, outfile, fail);
        fail++;
        str = strtok (NULL,"\n");
    }
    if (mas) {
        free(mas);
    }
    
}

int main(int argc, char  **argv) {
    if (argc < 2) {
        printf("Неверный ввод\n");
        return -1;
    }
    char *flag = argv[1];
    char out_name[17] = "file_output.txt";
    FILE *outfile = fopen(out_name, "w");
    if (outfile == NULL) {
        printf("Файл для вывода не создался\n");
        return -1;
    }
    printf("Пример ввода: ./task -fi files.txt\n");
    printf("Пример ввода: ./task -cin\n");
    printf("Пример ввода: ./aboba -arg n_files file2.txt file1.txt\n");
    if (!strcmp(flag, "-fi")) {
        if (argc != 3) {
            printf("Неверный ввод\n");
            return -1;
        }
        FILE *file = fopen(argv[2], "r");
        if (file == NULL) {
            printf("Ошибка открытия файла\n");
            return -1;
        }
        flag_fi(file, outfile);
        fclose(file);
    }
    else if (!strcmp(flag, "-cin")) {
        if (argc != 2) {
            printf("Неверный ввод\n");
            return -1;
        }
        flag_cin(outfile, out_name);
    }
    else if (!strcmp(flag, "-arg")) {
        if (argc < 3) {
            printf("Неверный ввод\n");
            return -1;
        }
        int nof = svoe_atoi(argv[2]);
        if (nof <= 0) {
            printf("Неверно задано количество файлов\n");
            return -1;
        }
        if (argc != (nof + 3)) {
            printf("Неверное количество введенных файлов\n");
            return -1;
        }
        unsigned int fail = 1;
        for (int i = 3; i <= (nof + 2); i++) {
            char *str = argv[i];
            write_file(str, outfile, fail);
            fail++;
        }
    }
    else {
        printf("Неверный ввод\n");
        return -1;
    }
    fclose(outfile);
    return 0;
}


