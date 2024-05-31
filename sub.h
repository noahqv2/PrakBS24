#ifndef SUB_H_INCLUDED
#define SUB_H_INCLUDED
#define KEYLENGTH 100
struct keyStore{
    char key[KEYLENGTH];
    char data[KEYLENGTH];
};
typedef struct keyStore keystruct;
typedef struct {
    int subscriber_id;
    keystruct subbeddata;
    int amount_subscriptions;
}Subbedkeys;
Subbedkeys* keysubber;

#endif // SUB_H_INCLUDED






char* befehl;
char* eingabekey;
char* eingabevalue;


char* stripstr(char* str);

void splitstr(char* str);

int checkcmd(char* str);

Subbedkeys* createMemBlock(Subbedkeys* keysubber,int size);
