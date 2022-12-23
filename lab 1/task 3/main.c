#include <stdio.h>
#include <string.h>
#include <ctype.h>

void only_alpha(FILE* file, FILE* outfile) {
    char symb;
    while ((symb = fgetc(file)) != EOF) {
        if (!isdigit(symb)) {
            fprintf(outfile, "%c", symb);
        }
    }
}

void count_alpha(FILE* file, FILE* outfile) {
    char symb;
    int counter = 0;
    while((symb = fgetc(file)) != EOF) {
        if (isalpha(symb)) {
            counter++;
        }
        if (symb == '\n') {
            fprintf(outfile, "%d\n", counter);
            counter = 0;
        }
    }
}

void count_symb(FILE* file, FILE* outfile) {
    char symb;
    int counter = 0;
    while((symb = fgetc(file)) != EOF) {
        if (!isalpha(symb) && !isdigit(symb) && (symb != ' ')) {
            if (symb == '\n') {
                fprintf(outfile, "%d\n", counter);
                counter = 0;
            }
            else {
                counter++;
            }
        }
    }
}

void asci(FILE* file, FILE* outfile) {
    char symb;
    while((symb = fgetc(file)) != EOF) {
        if (isdigit(symb)) {
            fprintf(outfile, "%c", symb);
        }
        else {
            fprintf(outfile, "%d", symb);
        }
    }
}

void change_lex(FILE* file, FILE* outfile) {
    char symb;
    int count_lex = 1;
    while((symb = fgetc(file)) != EOF) {
        if ((symb == ' ') || (symb == '\n')) {
            while ((symb == ' ') || (symb == '\n')) {
                fprintf(outfile, "%c", symb);
                symb = fgetc(file);
            }
            if (symb != EOF) {
                count_lex ++;
            }
            else {
                break;
            }
        }
        if ((count_lex % 2 == 0) && (count_lex % 10 != 0)) {
            if (isalpha(symb)) {
                fprintf(outfile, "%c", tolower(symb));
            }
            else {
                fprintf(outfile, "%c", symb);
            }
        }
        else if (count_lex % 5 == 0) {
            if (symb == '\n') {
                fprintf(outfile, "\n");
                continue;
            }
            fprintf(outfile, "%d", symb);
        }
        else {
            fprintf(outfile, "%c", symb);
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 3){
        printf("Недостаточно аргументов\n");
        return -1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Невозможно открыть файл\n");
        return -1;
    }
    char symb = argv[2][0];
    if (!(symb == '-' || symb == '/' || symb == 'n')) {
        printf("Некорректно введен флаг\n");
        return -1;
    }
    char flag = argv[2][1];
    if (!flag) {
        printf("Не указан флаг\n");
        return -1;
    }
    FILE* outfile;
    if (symb == 'n') {
        if (argc != 4) {
            printf("Некорректный ввод аргументов\n");
            return -1;
        }
        outfile = fopen(argv[3], "w");
    }
    else {
        const char* path = argv[1];
        char title[100] = "out_";
        strcat(title, path);
        outfile = fopen(title, "w");
    }
    if (outfile == NULL) {
        printf("Выходной файл не создался\n");
        return -1;
    }
    printf("Пример ввода: ./task file.txt -flag\n");
    if (flag == 'd') {
        only_alpha(file, outfile);
        fclose(file);
        fclose(outfile);
        return 0;
    }
    else if (flag == 'i') {
        count_alpha(file, outfile);
        fclose(file);
        fclose(outfile);
        return 0;
    }
    else if (flag == 's') {
        count_symb(file, outfile);
        fclose(file);
        fclose(outfile);
        return 0;
    }
    else if (flag == 'a') {
        asci(file, outfile);
        fclose(file);
        fclose(outfile);
        return 0;
    }
    else if (flag == 'f') {
        change_lex(file, outfile);
        fclose(file);
        fclose(outfile);
        return 0;
    }
    fclose(file);
    
    return -1;
}
