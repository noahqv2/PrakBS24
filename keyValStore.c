#include "keyValStore.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFFSIZE 1024


char* abspeichern(char* key, char* value) {
    int counter=0;
    char result[BUFFSIZE];
    struct keyStore keydata[KEYLENGTH];
    strcpy(keydata[counter].key, key); // for schleife einbauen wo hochgezählt wird, solange kein freier wert gefunden wird
    strcpy(result,value);
    strcpy(keydata[counter].data, value);
    sprintf(value,"PUT:%s:%s",key, result);
    printf("%s key \n %s data\n",keydata->key, keydata->data);
    return value;
    printf("entered abspeichern\n");
    int x=0;
    x=sizeof(value);
    x=x-3;
    /*for (int i =0;x>i;i++) {
        printf("entered loop \n");
        printf("%i",x);
        printf("%i",i);
        if (isalnum(value[i])==0) {
            printf("Allowed Input is limited to A-z & 0-9, operation failed.");
            return -1;
        }
    }*/
    if (strcmp(savedkey,key)==0) {
        printf("Erfolg");
        strcpy(savedkey, key);


    } else {
        printf("Invalid key, operation failed.");

    }

}
char* aufrufen(char* key) {
    //Keine Logik bis jetzt vorhanden, erst testen dann logik einfügen.
    struct keyStore keydata[KEYLENGTH];
    char tmp[sizeof(key)];
    //printf("%s \n", keydata[0].data);
    //sprintf(tmp,"GET:%s:%s",key, keydata[0].data);
    strcpy(key,tmp);
    return key;

}/*
char* del(char* key)
{
    //Keine Logik bis jetzt vorhanden, erst testen dann logik einfügen
    struct dataStore speicher;
    struct keyStore keychecker;
    strcpy(speicher.data1, "Leer");
    strcpy(keychecker.key1,"Leer");
    sprintf(key,"DEL:%s:%s_deleted",key,key);
    return key;
}*/