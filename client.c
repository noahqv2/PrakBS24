#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "keyValStore.h"
#include "sub.h"
#include "client.h"
#include <pthread.h>
#include <stdlib.h>
#define BUFFSIZE 1024

void write_to_client(int client_socket, char* str) {
    int msg_len = BUFFSIZE; //snprintf(str,0, "var:key:value")+1; old code / Could be assigned dynamically, for that you would have to get current values and keys.
    char* tmp=malloc(msg_len);
    // add newline back so there is a newline
    sprintf(tmp,"%s\n",str);
    strcpy(str,tmp);
    free(tmp);
    if (msg_len<0) {
        perror("failed");
        return;
    }
    if (write(client_socket, str,msg_len)<0) {
        perror("write failed");
    }
    printf("in write to client\n");
}
// Handles Client connection and doesnt return until terminated. Ignore IDE warning or else Server will wait until next client.
void *handle_client(void *arg) {
    char in[BUFFSIZE];
    char ausgabe[BUFFSIZE];
    client_args *args = (client_args*)arg;
    int client_socket = args->client_socket;
    int bytes_read = args->bytes_read;
    // Read data from client until an error occurs or client disconnects
    while (bytes_read  > 0) {
        // Process received data from client
        //printf("Client: %s\n", in);
        memset(in, 0, BUFFSIZE);
        printf("cleared input buff\n");
        memset(ausgabe,0,BUFFSIZE);
        printf("cleared output buff\n");
        int x=0;
        printf("Welche Operation wollen sie ausführen? PUT GET DEL QUIT\n");
        read(client_socket, in,BUFFSIZE);
        write(client_socket, in, BUFFSIZE);
        strcpy(in,stripstr(in));
        splitstr(in);

        if (befehl != NULL) {
            x=checkcmd(befehl);
            if (x <0) printf("Unknown Command \n");
            else {
                if (x==4) {
                    close(client_socket);
                    return NULL;
                }
                if (eingabekey != NULL) {
                    if (eingabevalue != NULL) {
                        if (x==1)  strcpy(ausgabe,abspeichern(eingabekey,eingabevalue));
                    } else if (x==2) {
                        strcpy(ausgabe, aufrufen(eingabekey));
                        printf("%s \n",ausgabe);
                        write_to_client(client_socket,ausgabe);
                    } else if (x==3) {
                        strcpy(ausgabe,leeren(eingabekey));
                        printf("%s \n", ausgabe);
                        write_to_client(client_socket,ausgabe);
                    } else if (eingabevalue==NULL) printf("Value needed, operation failed\n");
                }
            }
        }
        // Clear the input buffer

        //

        //free(args);
    }
}

