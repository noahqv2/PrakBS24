
#include <pthread.h>
#include "sub.h"


pthread_mutex_t mutex;

void init_ram();

void lock_and_unlock_mutex(int option, int clientnum);

char* abspeichern(char* key, char* value, int clientnum);

char* aufrufen(char* key, int clientnum);

char* leeren(char* key, int clientnum);

char* abonnieren(char* key, int clientnum, int option);

void check_subscribers(char* key, char* str);

char* deabonnieren(char* key, int keynum, Subbedkeys* keysubber);



