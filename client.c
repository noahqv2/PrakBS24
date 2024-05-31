#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "keyValStore.h"
#include "client.h"
#include <pthread.h>
#include <stdlib.h>
#define BUFFSIZE 1024


void write_to_client(int client_socket, char* str) {
    int msg_len = BUFFSIZE;
    char* tmp=malloc(msg_len);
    // add newline back so there is a newline
    sprintf(tmp,"%s\n",str);
    strcpy(str,tmp);
    free(tmp);

    if (write(client_socket, str,msg_len)<0) {
        perror("write failed");
    }
    //printf("in write to client\n");
}
// Handles Client connection and doesnt return until terminated. Ignore IDE warning or else Server will wait until next client.
// void *fun(void *arg) is required for pthread to work
void *handle_client(void *arg) {
    char in[BUFFSIZE];
    char ausgabe[BUFFSIZE];

    if(mutex_init_status != 0) {
        perror("Mutex initialization failed");
        exit(1);
    }
    // declaration of struct with var "args"
    client_args *args = (client_args*)arg;
    int client_socket = args->client_socket;
    int bytes_read = args->bytes_read;
    // Read data from client until an error occurs or client disconnects
    while (bytes_read  > 0) {
        //memset(eingabevalue,0,KEYLENGTH);

        // Process received data from client
        memset(in, 0, BUFFSIZE);
        //printf("cleared input buff\n");
        memset(ausgabe,0,BUFFSIZE);
        //printf("cleared output buff\n");
        int x=0;
        strcpy(ausgabe,"Welche Operation wollen sie ausführen? PUT GET DEL QUIT BEG END SUB\n");
        write(client_socket,ausgabe,BUFFSIZE);
        read(client_socket, in,BUFFSIZE);
        //write(client_socket, in, BUFFSIZE);
        strcpy(in,stripstr(in));
        splitstr(in);
        memset(ausgabe,0,BUFFSIZE);

        if (befehl != NULL) {
            x=checkcmd(befehl);
            if (x <0) printf("Unknown Command \n");
            else {
                if (x==4) {
                    close(client_socket);
                    return NULL;
                }
                if (x==5) {
                    lock_and_unlock_mutex(0, client_socket);

                } else if (x==6) {
                    lock_and_unlock_mutex(1, client_socket);

                } if (eingabekey != NULL) {
                    if (eingabevalue != NULL) {
                        if (x==1) {
                            memset(ausgabe,0,BUFFSIZE);
                            strcpy(ausgabe,abspeichern(eingabekey,eingabevalue,client_socket));
                            write_to_client(client_socket,ausgabe);
                            strcpy(eingabevalue,"");


                        }
                    } else if (x==2) {
                        strcpy(ausgabe, aufrufen(eingabekey, client_socket));
                        printf("%s \n",ausgabe);
                        write_to_client(client_socket,ausgabe);
                    } else if (x==3) {
                        strcpy(ausgabe,leeren(eingabekey,client_socket));
                        printf("%s \n", ausgabe);
                        write_to_client(client_socket,ausgabe);
                    } else if (x==7) {
                        strcpy(ausgabe,abonnieren(eingabekey,client_socket,0));
                        printf("%s \n",ausgabe);
                        write_to_client(client_socket,ausgabe);
                    }
                    else if (eingabevalue==NULL) printf("Value needed, operation failed\n");
                }
            }
        }
    }
}

