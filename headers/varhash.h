#include "proglist.h"
#define HASH_SIZE 100000
typedef struct map{
	char *key;
	Elem value;
	struct map *next;
} *MAP;

MAP lookupHash(char *s);
void insertHash(char *s,Elem value);
void initHash();
MAP hashTable[HASH_SIZE];
int hashChar(char *s);

//LABEL HASH
#define LABELMAX 100000
typedef struct labelist {
    char *name;
    PROGLIST proglist;
    struct labelist *next;
} *LABELIST;

LABELIST labels[LABELMAX];
void initLabelist(PROGLIST l);
void insertLabel(char *s, PROGLIST l);
PROGLIST gotoLabel(char *s);
void printLabelist(); //Label checker

