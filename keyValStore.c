#include "keyValStore.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define BUFFSIZE 1024

struct keyStore {
    char key1[BUFFSIZE];
    char key2[BUFFSIZE];
};
int abspeichern(char* key, char* value) {
    printf("entered abspeichern\n");
    int x=0;
    x=sizeof(value);
    x=x-3;
    for (int i =0;x>i;i++) {
        printf("entered loop \n");
        printf("%i",x);
        printf("%i",i);
        if (isalnum(value[i])==0) {
            printf("Allowed Input is limited to A-z & 0-9, operation failed.");
            return -1;
        }
    }
    if (strcmp(savedkey,key)==0) {
        printf("Erfolg");
        strcpy(savedkey, key);
        return 0;
    } else {
        printf("Invalid key, operation failed.");
        return -1;
    }

}
int aufrufen(char* key, char* res)
{

}
int del(char* key);