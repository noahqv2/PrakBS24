#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined  _WIN64 || defined __CYGWIN__
    #include<winsock2.h>
    #include<Ws2tcpip.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <netinet/in.h>
#endif
#include <sys/types.h>

//int main(void) {
//    printf("Hello, World!\n");
//    return 0;
//}
void error(const char *msg)
{
    perror(msg);
    exit((1));
}

int main(int argc , char *argv[])
{
#if defined _WIN64 || defined __CYGWIN__
    WSADATA wsaData;

    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
#endif

    if(argc < 2)
    {
        fprintf(stderr, "Port nicht genannt. Programm wird geschlossen");
        exit(1);
    }
    int sockfd , newsockfd , portno, n;
    char buffer[255];

    struct sockaddr_in serv_addr , cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if(sockfd < 0)
    {
        error("Error opening socket.");
    }
    __builtin_bzero((char *)&serv_addr, sizeof(serv_addr));
    portno =atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof
        (serv_addr)) < 0)
        error("Binding Failed");


}