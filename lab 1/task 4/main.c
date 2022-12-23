#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int string_sep(char *mas, FILE* outfile) {
    char *str = NULL;
    char *sec_lex = NULL;
    char *third_lex = NULL;
    char *first_lex = NULL;
    str = strtok(mas, " ");
    int count_lex = 0;
    while (str != NULL) {
        if (count_lex == 0) {
            first_lex = str;
        }
        else if (count_lex == 1) {
            sec_lex = str;
        }
        else if (count_lex == 2){
            third_lex = str;
        }
        str = strtok (NULL, " ");
        count_lex ++;
    }
    if (count_lex != 3) {
        return -1;
    }
    fprintf(outfile, "%s ", third_lex);
    fprintf(outfile, "%s ", first_lex);
    fprintf(outfile, "%s\n", sec_lex);
    return 0;
}

void text_sep(FILE* file, FILE* outfile) {
    char* mas = NULL;
    int buff = 100;
    mas = (char*)malloc(sizeof(char) * (buff + 1));
    if (mas == NULL) {
        printf("Массив не создался\n");
    }
    int tek_poz = 0;
    char symb;
    char* mas2;
    while ((symb = fgetc(file)) != EOF) {
        if (symb == '\n') {
            int i = string_sep(mas, outfile);
            if (i == -1) {
                printf("Неверный ввод таблицы (либо есть пустые строки, либо неверное количество лексем)\n");
                return ;
            }
            tek_poz = 0;
            mas = (char*)malloc(sizeof(char) * (buff + 1));
        }
        else {
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
                mas = mas2;
                mas[tek_poz] = symb;
                tek_poz ++;
            }
        }

    }
    if (mas) {
        free(mas);
    }
}

int main(int argc, char **argv) {
    if (argc > 2) {
        printf("Некорректный запуск\n");
        return -1;
    }
    FILE *file = fopen(argv[1], "r+");
    if (file == NULL) {
        printf("Неверный ввод\n");
        return -1;
    }
    const char * name_outfile = "amongus";
    FILE *outfile = fopen(name_outfile, "w+");
    if (outfile == NULL) {
        printf("Не получилось создать еще один файл\n");
        fclose(file);
        return -1;
    }
    text_sep(file, outfile);
    if (rename(name_outfile, argv[1]) == -1) {
          printf("Ошибка\n");
        return -1;
    }
    fclose(outfile);
    return 0;
}
