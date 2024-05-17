#include "keyValStore.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFSIZE 1024


struct keyStore keydata[KEYLENGTH];
int counter=0;
// function to save non exisiting key and data
char* abspeichern(char* key, char* value) {
    counter=0;
    char result[BUFFSIZE];
    // for loop to check for alphanumericity
    for(int i=0; key[i] != '\0';i++) {
        if (isalnum(key[i])==0) {
            sprintf(value,"Non alphanummerical is not allowed, operation failed");
            printf("%s \n",value);
            return "";
        } else {
            printf("%c Isalnum \n", key[i]);
        }
    }
    // uses while loop with key to check which keychain pairing is used
    while (keydata[counter].key !=NULL || keydata[counter].key != "" || keydata[counter].data!=NULL ||keydata[counter].data !="") {
        if (keydata[counter].data ==NULL || keydata[counter].data =="" || strcmp(keydata[counter].data,result)==0) {
            break;
        } else {
            counter++;
        }
    }
    strcpy(keydata[counter].key, key);
    strcpy(result,value);
    strcpy(keydata[counter].data, value);
    sprintf(value,"PUT:%s:%s",key, result);
    strcpy(result,"");
    return value;
}
// function to call from existing key and return associated data
char* aufrufen(char* key) {
    int keychecker=0;
    // checks every keypair to see if it exists and returns if found
    for (int i=0; i<100; i++) {
        if (strcmp(keydata[i].key,key)==0) {
            int totalsize =snprintf(NULL,0,"GET:%s:%s",key, keydata[i].data) +1;
            char* tmp =malloc(totalsize);
            sprintf(tmp,"GET:%s:%s",key, keydata[i].data);
            strcpy(key,tmp);
            free(tmp);
            return key;
        }
    }
    // checks if key exists
    do{
        counter=keychecker;
        if (strcmp(keydata[counter].key,"")==0) {
            //printf("%s keydata\n",keydata[keychecker].key);
            int totalsize =snprintf(NULL,0,"GET:%s:%s",key, keydata[keychecker].data) +1;
            char* tmp =malloc(totalsize);
            sprintf(tmp,"GET:%s:%s_nonexistent",key, key);
            strcpy(key,tmp);
            free(tmp);
            return key;
            }
        keychecker++;
    }while (strcmp(key,keydata[counter].key)!=0);
    // Failsafe return
    int totalsize =snprintf(NULL,0,"GET:%s:%s",key, keydata[keychecker].data) +1;
    char* tmp =malloc(totalsize);
    sprintf(tmp,"GET:%s:%s",key, keydata[counter].data);
    strcpy(key,tmp);
    free(tmp);
    return key;
}
// function to clear key and associated data
char* leeren(char* key)
{

    bool exists = false;
    for (int i=0; i<100; i++) {
        if (strcmp(keydata[i].key,key)==0) {
            exists = true;
        }
    }
    if (exists ==false) {
        int totalsize = snprintf (NULL,0,"%s%s does not exist",key,key) +1;
        char* tmp=malloc(totalsize);
        sprintf(tmp,"DEL:%s:%s_does not exist",key,key);
        strcpy(key,tmp);
        free(tmp);
        return key;

    }
    int keychecker=0;
    // checks keypairs to see which key pair it is
    do{
        if (strcmp(key,keydata[keychecker].key)==0) {
            counter=keychecker;
        } else {
            keychecker++;
            counter=keychecker;

        }
    }while (strcmp(key,keydata[keychecker].key)!=0);
    // Allocates memory
    int totalsize = snprintf (NULL,0,"DEL:%s:%s",key, keydata[keychecker].data) +1;
    char* tmp=malloc(totalsize);
    sprintf(tmp,"DEL:%s:%s_deleted",key,keydata[keychecker].data);
    strcpy(keydata[keychecker].data, "");
    strcpy(keydata[keychecker].key,"");
    counter=keychecker;
    strcpy(key,tmp);
    free(tmp);
    return key;
}