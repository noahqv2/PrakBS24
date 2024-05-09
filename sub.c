#include <ctype.h>
#include <stdio.h>
#include <string.h>
#ifndef SUB_H
#define SUB_H

#include "sub.h"
#include "keyValStore.h"
#endif // SUB_H

int i=0;

char* stripstr(char *str) {
    str[strcspn(str, "\n")] = 0;
    str[strcspn(str, "\r")] = 0;
    return str;
}
/*struct Teile {
    char befehl[5];
    char key[10];
    char data[10]; */
};
char* splitstr(char *str) {



    char *token=strtok(str, ":");
    while (token != NULL) {

    }
}