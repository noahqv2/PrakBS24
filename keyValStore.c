#include "keyValStore.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int abspeichern(char* key, char* value) {
    for (int i =0;key[i];i++) {
        if (isalnum(key[i])==0) {
            printf("Allowed Input is limited to A-z & 0-9, operation failed.");
            return -1;
        }
    }
    if (strcmp(savedkey,key)==0) {
        strcpy(savedkey, key);
        return 0;
    } else {
        printf("Invalid key, operation failed.");
        return -1;
    }

}
int get(char* key, char* res) {

}
int del(char* key);