#define KEYLENGTH 100
#include <pthread.h>
struct keyStore {
    char key[KEYLENGTH];
    char data[KEYLENGTH];
};
pthread_mutex_t mutex;

void lock_and_unlock_mutex(int option, int clientnum);

char* abspeichern(char* key, char* value, int clientnum);

char* aufrufen(char* key, int clientnum);

char* leeren(char* key, int clientnum);