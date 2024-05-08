#include "keyValStore.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define BUFFSIZE 1024

struct keyStore {
    char key1[BUFFSIZE];
    char key2[BUFFSIZE];
    char key3[BUFFSIZE];
};
struct dataStore {
    char data1[BUFFSIZE];
    char data2[BUFFSIZE];
    char data3[BUFFSIZE];
};
char* abspeichern(char* key, char* value) {
    char result[BUFFSIZE];
    struct dataStore speicher;
    struct keyStore keycheck;
    strcpy(keycheck.key1, key);
    strcpy(result,value);
    strcpy(speicher.data1, value);
    sprintf(value,"PUT:%s:%s",key, result);
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
char* aufrufen(char* key, char* res)
{
    //Keine Logik bis jetzt vorhanden, erst testen dann logik einfügen.
    struct dataStore speicher;
    struct keyStore keychecker;
    strcpy(speicher.data1,res);
    printf("%s", res);
    return res;

}
char* del(char* key)
{
    //Keine Logik bis jetzt vorhanden, erst testen dann logik einfügen
    struct dataStore speicher;
    struct keyStore keychecker;
    strcpy(speicher.data1, "Leer");
    strcpy(keychecker.key1,"Leer");
    sprintf(key,"DEL:%s:%s_deleted",key,key);
    return key;
}