#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef SUB_H
#define SUB_H
#include "sub.h"
#include "keyValStore.h"
#endif // SUB_H



// function to clean input
char* stripstr(char *str) {
    str[strcspn(str, "\n")] = 0;
    str[strcspn(str, "\r")] = 0;
    return str;
}
// function to seperate input by colon
void splitstr(char *str) {
    befehl=strtok(str, ":");
    if (befehl!= NULL) {
        eingabekey= strtok(NULL,":");
    }
    if (eingabekey!= NULL) {
        eingabevalue= strtok(NULL, ":");
    }
}
// fuction to check input for given command
int checkcmd(char *str) {
    if (strcmp(str,"PUT")==0) {
        return 1;
    }else if (strcmp(str,"GET")==0) {
        return  2;
    }else if (strcmp(str,"DEL")==0) {
        return 3;
    }else if (strcmp(str,"QUIT")==0) {
        return 4;
    }else if (strcmp(str,"BEG")==0) {
        return 5;
    }else if (strcmp(str,"END")==0) {
        return 6;
    }else if(strcmp(str,"SUB")==0) {
        return 7;
    } else return -1;
}
/*Subbedkeys* createMemBlock(Subbedkeys* keysubber, int size) {
    printf("Before creating keysub malloc\n");
    keysubber=malloc(sizeof(keysubber));
    printf("Before creating subbeddata malloc\n");
    keysubber->subbeddata = malloc(size);
    return keysubber;
} */

