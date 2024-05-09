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
    while (keydata[counter].key !=NULL || keydata[counter].key != "" || keydata[counter].data!=NULL ||keydata[counter].data !=""){
        printf("In schleife\n");
        printf("%s  wert in data\n ",keydata[counter].data);
        if (keydata[counter].data ==NULL || keydata[counter].data =="" || strcmp(keydata[counter].data,result)==0) {
            printf("Hier drinnen?\n");
            break;
        } else {
            printf("Oder hier?\n");
            counter++;
        }

    }
    printf("%i zähler\n",counter);
    strcpy(keydata[counter].key, key); // for schleife einbauen wo hochgezählt wird, solange kein freier wert gefunden wird
    strcpy(result,value);
    strcpy(keydata[counter].data, value);
    sprintf(value,"PUT:%s:%s",key, result);
    strcpy(result,"");
    printf("%s key \n%s data\n",keydata[counter].key, keydata[counter].data);
    printf("in slot %i \n",counter);
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
    int keychecker=0;

    char test[BUFFSIZE];
    do{
        if (strcmp(key,keydata[keychecker].key)==0) {
            printf("Keychecker B\n");
            counter=keychecker;
        } else {

            if (strcmp(keydata[counter].key,"")==0 || strcmp(keydata[counter].key,test)==0) {
                /*if (strcmp(keydata[keychecker].key,test)==0) {
                    printf("Keychecker D\n");
                    break;
                } else*/ if (strcmp(keydata[counter].data,"")==0 ) {
                    printf("Keychecker E\n");
                    printf("from%i",counter);
                    int totalsize =snprintf(NULL,0,"GET:%s:%s",key, keydata[counter].data) +1;
                    char* tmp =malloc(totalsize);
                    sprintf(tmp,"GET:%s:%s",key, keydata[counter].data);
                    strcpy(key,tmp);
                    free(tmp);
                    return key;
                }
                else {
                    printf("%s keydata\n",keydata[keychecker].key);
                    printf("%s test\n",test);
                    printf("Keychecker C\n");
                    int totalsize =snprintf(NULL,0,"GET:%s:%s",key, keydata[keychecker].data) +1;
                    char* tmp =malloc(totalsize);
                    sprintf(tmp,"GET:%s:%s_nonexistent",key, key);
                    strcpy(key,tmp);
                    free(tmp);
                    return key;
                }
            }
            counter=keychecker;
            keychecker++;

            printf("Keychecker A\n");

        }
    }while (strcmp(key,keydata[counter].key)!=0);
    printf("%i zäääähler\n",counter);
    printf("%swert in data\n", keydata[counter].data);
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