#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "sub.h"



char* stripstr(char *str) {
    str[strcspn(str, "\n")] = 0;
    str[strcspn(str, "\r")] = 0;
    return str;
}
struct Teile {
    char befehl[5];
    char key[10];
    char data[10];
};
char* splitstr(char *str) {


    char *token=strtok(str, ":");
    while (token != NULL) {

    }
}