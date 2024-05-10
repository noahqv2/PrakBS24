#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#ifndef MAIN_H
#define MAIN_H
#include "sub.h"
#include "keyValStore.h"
#endif // MAIN_H

#define BUFSIZE 1024 // Größe des Buffers
#define TRUE 1
#define ENDLOSSCHLEIFE 1
#define PORT 4711


int main() {
    int rfd; // Rendevouz-Descriptor
    int cfd; // Verbindungs-Descriptor
    char full_input[BUFSIZE];
    int input_length = 0;


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


        int pid;
        //Erstellt eine Fork um mehrere Clients gleichzeitig zu bearbeiten
        // fork returned 0 falls eine fork erfolgreich erstellt wurden konnte,
         //if ((pid = fork()) == 0) {
            // char* befehl;
             //char* eingabekey;
             //char* eingabevalue;
             char ausgabe[BUFSIZE];


             //printf("success, \n PID:%i \n",getpid());
             // Zurückschicken der Daten, solange der Client welche schickt (und kein Fehler passiert)
             while (bytes_read > 0) {
                 int x=0;

                 memset(in,0,1024);
                 //write(cfd, in, bytes_read);
                 //bytes_read = read(cfd, in, BUFSIZE);
                 printf("Welche Operation wollen sie ausführen? PUT GET DEL QUIT\n");
                 read(cfd, in,BUFSIZE);
                 write(cfd, in, BUFSIZE);
                 strcpy(in,stripstr(in));
                 //printf("%s in string\n",in);
                 splitstr(in);
                 if (befehl != NULL) {
                     x=checkcmd(befehl);
                     if (x <0) {
                         printf("Unknown Command \n");
                     }else {
                         if (x==4) {
                             close(cfd);
                             break;
                         }
                         if (eingabekey != NULL) {
                             if (eingabevalue != NULL) {
                                 if (x==1) {
                                     strcpy(ausgabe,abspeichern(eingabekey,eingabevalue));
                                 }
                             } else if (eingabevalue==NULL) {
                                 printf("Value needed, operation failed\n");
                             }
                             if (x==2) {
                                 //printf("%s eingabekey\n",eingabekey);
                                 strcpy(ausgabe, aufrufen(eingabekey));
                                 printf("%s Ausgabe\n",ausgabe);
                             }
                             if (x==3) {
                                 strcpy(ausgabe,leeren(eingabekey));
                                 printf("%s Ausgabe\n", ausgabe);
                             }
                         }
                     }
                 }
                 //Leert den String
                 memset(in,0,1024);
             }
         // Falls kein Fork erstell wurde wird die verbindung wieder geschlossen
     //    } else {
       //      printf("Fehler beim fork erstellen, %i", pid);
         //    close(cfd);;

        // }

       //  close(cfd);
    }

    // Rendevouz Descriptor schließen
    //close(rfd);

}