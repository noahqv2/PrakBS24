#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "sub.h"
#include "keyValStore.h"

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
        bytes_read = read(cfd, in, BUFSIZE);


        int pid;
        //Erstellt eine Fork um mehrere Clients gleichzeitig zu bearbeiten
        // fork returned 0 falls eine fork erfolgreich erstellt wurden konnte,
         //if ((pid = fork()) == 0) {
             int auswahl;
             char eingabekey[BUFSIZE];
             char eingabevalue[BUFSIZE];
             //printf("success, \n PID:%i \n",getpid());
             // Zurückschicken der Daten, solange der Client welche schickt (und kein Fehler passiert)
             while (bytes_read > 0) {

                 //write(cfd, in, bytes_read);
                 //bytes_read = read(cfd, in, BUFSIZE);
                 printf("Welche Operation wollen sie ausführen? PUT GET DELETE\n");
                 memset(in,0,1024);
                 //fgets(full_input, sizeof(full_input),stdin);
                 read(cfd, in,BUFSIZE);
                 write(cfd, in, BUFSIZE);
                 //memset(in,0,1024);
                 //printf("Oben liest\n");
                 //read(cfd, in, BUFSIZE);
                 //write(cfd,in,BUFSIZE);
                 //printf("Oben schreibt\n");
                 in[strcspn(in, "\n")] = 0;
                 in[strcspn(in, "\r")] = 0;
                // write(rfd, full_input, bytes_read);


                 if (strcmp(in,"PUT")==0) {
                     printf("Geben sie ihren key ein\n");
                     read(cfd, in, BUFSIZE);
                     write(cfd, in, BUFSIZE);
                    // fgets(eingabekey, sizeof(eingabekey), stdin);
                     in[strcspn(in, "\n")] = 0;
                     in[strcspn(in, "\r")] = 0;
                     strcpy(eingabekey, in);
                     //write(cfd,in , BUFSIZE);

                     //bytes_read = read(cfd, eingabekey, BUFSIZE);
                     printf("Geben Sie Ihre Data an\n");
                //     fgets(eingabevalue, sizeof(eingabevalue), stdin);
                     read(cfd,in, BUFSIZE);
                     write(cfd,in, BUFSIZE);
                     in[strcspn(in, "\n")] = 0;
                     in[strcspn(in, "\r")] = 0;
                     //write(cfd,eingabevalue , bytes_read);
                     strcpy(eingabevalue,in);
                     abspeichern(eingabekey, eingabevalue);
                        printf("end of loop\n");


                 } else {
                     printf("Failed\n");
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