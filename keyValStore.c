#include "keyValStore.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFSIZE 1024


struct keyStore keydata[KEYLENGTH];
int counter=0;
char* abspeichern(char* key, char* value) {
    counter=0;
    char result[BUFFSIZE];
    if (strcmp(value,"")==0) {
        printf("Value needed, operation failed\n");
        return "";
    }
    for(int i=0; key[i] != '\0';i++) {
        if (isalnum(key[i])==0) {
            sprintf(value,"Non alphanummerical is not allowed, operation failed");
            printf("%s \n",value);
            return "";
        } else {
            printf("%c Isalnum \n", key[i]);
        }
    }
    while (keydata[counter].key !=NULL || keydata[counter].key != "" || keydata[counter].data!=NULL ||keydata[counter].data !="") {
        if (keydata[counter].data ==NULL || keydata[counter].data =="" || strcmp(keydata[counter].data,result)==0) {
            break;
        } else {
            counter++;
        }
    }
    strcpy(keydata[counter].key, key); // for schleife einbauen wo hochgezählt wird, solange kein freier wert gefunden wird
    strcpy(result,value);
    strcpy(keydata[counter].data, value);
    sprintf(value,"PUT:%s:%s",key, result);
    strcpy(result,"");
    return value;
}
char* aufrufen(char* key) {
    int keychecker=0;

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
    //printf("%swert in data\n", keydata[counter].data);
    int totalsize =snprintf(NULL,0,"GET:%s:%s",key, keydata[keychecker].data) +1;

    char* tmp =malloc(totalsize);
    sprintf(tmp,"GET:%s:%s",key, keydata[counter].data);
    strcpy(key,tmp);
    free(tmp);
    return key;
}
char* leeren(char* key)
{
    int keychecker=0;
    do{
        if (strcmp(key,keydata[keychecker].key)==0) {
            printf("Keychecker B\n");
            counter=keychecker;
        } else {
            keychecker++;
            counter=keychecker;
            printf("Keychecker A\n");

        }
    }while (strcmp(key,keydata[keychecker].key)!=0);
    //Keine Logik bis jetzt vorhanden, erst testen dann logik einfügen
    int totalsize = snprintf (NULL,0,"GET:%s:%s",key, keydata[keychecker].data) +1;
    char* tmp=malloc(totalsize);
    sprintf(tmp,"DEL:%s:%s_deleted",key,keydata[keychecker].data);
    strcpy(keydata[keychecker].data, "");
    strcpy(keydata[keychecker].key,"");
    counter=keychecker;
    strcpy(key,tmp);
    free(tmp);
    return key;
}