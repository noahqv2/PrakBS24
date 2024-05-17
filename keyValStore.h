#define KEYLENGTH 100
struct keyStore {
    char key[KEYLENGTH];
    char data[KEYLENGTH];
};
char* abspeichern(char* key, char* value);

char* aufrufen(char* key);

char* leeren(char* key);