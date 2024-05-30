#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#ifndef MAIN_H
#define MAIN_H
#include "sub.h"
#include "keyValStore.h"
#include "client.h"
#endif // MAIN_H

#define BUFSIZE 1024 // Größe des Buffers
#define TRUE 1
#define ENDLOSSCHLEIFE 1
#define PORT 5678


int main() {
    int rfd; // Rendevouz-Descriptor
    int cfd; // Verbindungs-Descriptor
    int input_length = 0;

    pthread_mutex_init(&mutex, NULL);

    struct sockaddr_in client; // Socketadresse eines Clients
    socklen_t client_len; // Länge der Client-Daten
    char in[BUFSIZE]; // Daten vom Client an den Server
    int bytes_read; // Anzahl der Bytes, die der Client geschickt hat


    // Socket erstellen
    rfd = socket(AF_INET, SOCK_STREAM, 0);
    if (rfd < 0 ){
        fprintf(stderr, "socket konnte nicht erstellt werden\n");
        exit(-1);
    }


    // Socket Optionen setzen für schnelles wiederholtes Binden der Adresse
    int option = 1;
    setsockopt(rfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));


    // Socket binden
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    int brt = bind(rfd, (struct sockaddr *) &server, sizeof(server));
    if (brt < 0 ){
        fprintf(stderr, "socket konnte nicht gebunden werden\n");
        exit(-1);
    }


    // Socket lauschen lassen
    int lrt = listen(rfd, 5);
    if (lrt < 0 ){
        fprintf(stderr, "socket konnte nicht listen gesetzt werden\n");
        exit(-1);
    }
    //Unendliche Schleife weil der Server solange laufen soll wie das Programm läuft.
    while (ENDLOSSCHLEIFE) {
        // Verbindung eines Clients wird entgegengenommen
        cfd = accept(rfd, (struct sockaddr *) &client, &client_len);
        // Lesen von Daten, die der Client schickt
        printf("Press ENTER to begin\n");
        bytes_read = read(cfd, in, BUFSIZE);

        client_args *args = malloc(sizeof(client_args));
        // feeds data into struct declared in client.h to be accessable in client.c
        args->client_socket = cfd;
        args->bytes_read = bytes_read;



        // gives name of thread then creates it.
        pthread_t thread;
        pthread_create(&thread, NULL, handle_client,args);
        printf("created thread\n");
        // detaches it so it frees up after QUIT is entered or client disconnectes
        pthread_detach(thread);
        printf("Detached Thread \n");


        //handle_client(cfd, bytes_read);
        printf("outside\n");


    }
}