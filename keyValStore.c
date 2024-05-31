#include "keyValStore.h"
#include "client.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef SUB_H
#define SUB_H
#include "sub.h"
#endif // SUB_H
#define BUFFSIZE 1024
#define MAX_SUBSCRIBERS 10
struct keyStore keydata[KEYLENGTH];
Subbedkeys subscribers[MAX_SUBSCRIBERS];
int amountsubs=0;

int check = 0;
int counter=0;
// function to save non exisiting key and data
void lock_and_unlock_mutex(int option, int clientnum) {
    if (option == 0) {
        pthread_mutex_lock(&mutex);
        printf("Transaction locked\n");
        check = clientnum;
    } else if (option==1) {
        if (check ==0 || check == clientnum) {
            pthread_mutex_unlock(&mutex);
            printf("Transaction unlocked \n");
            check = 0;
        }
    }
}
char* abspeichern(char* key, char* value,int clientnum) {
    counter=0;
    printf("%i checking if locked..\n",check);
    if (check >0 && clientnum!=check) {
        return "Currently locked." ;
    }

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
        } else if (strcmp(keydata[counter].key,key)==0) {
            printf("deleteing old pair\n");
            int totalsize =10000;//snprintf(NULL,0,"GET:%s:%s",key, value) +1;
            char* tmp =malloc(totalsize);
            char* tmp2=malloc(totalsize);
            strcpy(tmp,key);
            strcpy(tmp2,value);
            leeren(key,clientnum);
            memset(key,0,KEYLENGTH);
            strcpy(key,tmp);
            strcpy(value,tmp2);
            free(tmp);
            free(tmp2);
            goto keyabspeichern;
        }else {
            counter++;
        }
    }
    keyabspeichern:
    strcpy(keydata[counter].key, key);
    strcpy(result,value);
    strcpy(keydata[counter].data, value);
    sprintf(value,"PUT:%s:%s",key, result);
    check_subscribers(keydata[counter].key, value);

    strcpy(result,"");
    return value;
}
// function to call from existing key and return associated data
char* aufrufen(char* key, int clientnum) {




    int keychecker=0;
    printf("%i checking if locked..\n",check);
    if (check >0 && clientnum!=check) {
        return "Currently locked." ;
    }


    printf("before if\n");
    if (subscribers[0].subscriber_id != 0) {
        printf("Inside of if\n");
        printf("%s lol\n",subscribers[0].subbeddata.key);
        printf("ID:%i NRAMT:%i",subscribers[0].subscriber_id, subscribers[0].amount_subscriptions);
       //write_to_client(clientnum,key);
    }
    printf("After if \n");
    // checks every keypair to see if it exists and returns if found
    for (int i=0; i<100; i++) {
        if (strcmp(keydata[i].key,key)==0) {
            printf("decided it is %i pair \n",i);
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
char* leeren(char* key, int clientnum)
{

    if (check >0 && clientnum!=check) {
        return "Currently locked." ;
    }
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
    strcpy(key,tmp);
    check_subscribers(keydata[counter].key, key) ;

    strcpy(keydata[keychecker].data, "");
    strcpy(keydata[keychecker].key,"");
    counter=keychecker;


    free(tmp);
    return key;
}
// function to subscribe a client to a key
char* abonnieren(char* key, int clientnum, int option) {
    printf("%s \n",key);
    for (int i=0; i<100; i++) {

        if (strcmp(keydata[i].key,key)==0) {
            if (option==1) {
                strcpy(key,deabonnieren(0,i,keysubber));
                return key;
            }
            if (option==0) {

                printf("1\n");
                subscribers[clientnum].subscriber_id = clientnum;
                for (int l=0;l<10;l++) {


                    if (strcmp(keydata[l].key,key)==0) {
                        amountsubs++;
                        strcpy(subscribers[l].subbeddata.key, key);
                        strcpy(subscribers[l].subbeddata.data,keydata[i].data);
                        int totalsize =snprintf(NULL,0,"SUB:%s:%s",key, keydata[l].data) +1;
                        char* tmp =malloc(totalsize);
                        sprintf(tmp,"SUB:%s:%s",key, keydata[l+4].data);
                        strcpy(key,tmp);
                        free(tmp);
                        return key;
                    }
                }
            }
        }
    }
    return "key does not exit";
}
// function that writes to the clients that are subscribed to that specific key value
void check_subscribers(char* key, char* str) {
    char* result [BUFFSIZE];
    for(int i = 0; i<10;i++) {
        if (subscribers[i].subscriber_id !=0) {
            for (int j=0; j<10; j++) {
                if (subscribers[j].subbeddata.key != NULL) {
                    if (strcmp(key,subscribers[j].subbeddata.key)==0)  {
                        if (strcmp(subscribers[j].subbeddata.data,"") !=0 ) {
                            strcpy(key,stripstr(key));
                            write_to_client(subscribers[i].subscriber_id,str);
                            break;
                        }
                    }
                }
            }
        }
    }
}
// No plans to implement
char* deabonnieren(char* key, int keynum,Subbedkeys* keysubber) {
    //keysubber=malloc(sizeof(Subbedkeys));
    if(keysubber==NULL) {
        return "not subscribed";
    }
    int totalsize =snprintf(NULL,0,"UNSUB:%s:%s",key, keydata[keynum].data) +1;
    char* tmp =malloc(totalsize);
    sprintf(tmp,"UNSUB:%s:%s",key, keydata[keynum].data);
    strcpy(key,tmp);
    free(tmp);
    //free(keysubbersubbeddata);
    //free(keysubber);
    return key;
}
//  printf("Inside of abonnieren.\n Clientnum:%i \n Amountofsubs:%i \n keysubkey %s\n keysubdata %s\n",clientnum,amountsubs,subscribers[l].subbeddata.key,subscribers[l].subbeddata.data);
