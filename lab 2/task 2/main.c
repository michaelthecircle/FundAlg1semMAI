#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void func_c(char* str1, char* str2, char* res){
    for(unsigned long i = 0; i < strlen(str1); i++){
        res[i] = str1[i];
    }
    for(unsigned long i = 0; i < strlen(str2); i++){
        res[strlen(str1) + i] = str2[i];
    }
}
void func_n(char* slovo, char* res) {
    unsigned long tek_poz = 0;
    for(unsigned long i = 0; i < strlen(slovo); i++){
        if (isdigit(slovo[i])) {
            res[tek_poz] = slovo[i];
            tek_poz++;
        }
    }
    for(unsigned long i = 0; i < strlen(slovo); i++){
        if (isalpha(slovo[i])) {
            res[tek_poz] = slovo[i];
            tek_poz++;
        }
    }
    for(unsigned long i = 0; i < strlen(slovo); i++){
        if (!((isdigit(slovo[i])) || (isalpha(slovo[i])))) {
            res[tek_poz] = slovo[i];
            tek_poz++;
        }
    }
}
    
int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Некорректный ввод\n");
        return 0;
    }
    else if (argc == 3 && argv[2][1] == 'c'){
        printf("Недостаточно аргументов для флага -с!\n");
        return 0;
    }
    else if (argc == 4 && argv[2][1] != 'c'){
        printf("Лишние аргументы!\n");
        return 0;
    }
    
    char flag = argv[2][1];
    char* string = argv[1];
    int count = 0;
    int i = 0;
    if (flag == 'l') {
        while (string[i++] != '\0') {
            count ++;
        }
        printf("%d\n", count);
        return 0;
    }
    else if (flag == 'r') {
        char *start = string;
        char *finish = string + strlen(string) - 1;
        char tek;
        while (start < finish) {
            tek = *start;
            *start = *finish;
            *finish = tek;
            start ++;
            finish --;
        }
        printf("%s\n", string);
        return 0;
    }
    else if (flag == 'u') {
        for(int j = 0; j < strlen(string); j += 2) {
            string[j] = toupper(string[j]);
        }
        printf("%s\n",string);
        return 0;
    }
    else if (flag == 'n') {
        char *arr = (char*)malloc(sizeof(char) * strlen(string));
        func_n(argv[1], arr);
        printf("%s\n", arr);
        free(arr);
        return 0;
    }
    else if (flag == 'c') {
        char *arr = (char*)malloc(sizeof(char) * (strlen(argv[1])+strlen(argv[3])));
        func_c(argv[1], argv[3], arr);
        printf("%s\n", arr);
        free(arr);
        return 0;
    }
    return 0;
}
