#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/varhash.h"
MAP lookupHash(char *s) {
    int index;
    index = hashChar(s);
    MAP p = hashTable[index];
    while(p) {
        if(hashChar(p->key) == index) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
void insertHash(char *s, Elem value) {
    int index;
    index = hashChar(s);
    MAP p;
    p = (MAP)malloc(sizeof(struct map));
    p->key = s;
    p->value = value;
    p->next = NULL;
    hashTable[index] = p;
}
void initHash() {
    for(int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}
int hashChar(char *s) {
    int total = 0, i = 0;
    //printf("%ld, %d\n",strlen(s),(int)s[i]);
    for(i = 0; i < strlen(s); i++) {
        total = total + (int)s[i];
    }
    //total/=1000;
    return total;
}


//Label Hash
void initLabelist(PROGLIST l) {
    while(l != NULL) {
        if(l->instruction.op == LABEL) {
            Elem x = l->instruction.first;
            insertLabel(getName(x), l->next);
        }
        l = l->next;
    }
}

void printLabelist() {
    //printf(" ");
    for(int i = 0; i < LABELMAX; i++) {
        if(labels[i] != NULL)printf("Key %d: %s\n", i, labels[i]->name);
    }
}
void insertLabel(char *s, PROGLIST l) {
    int index;
    index = hashChar(s);
    LABELIST p;
    p = (LABELIST)malloc(sizeof(struct labelist));
    p->name = s;
    p->proglist = l;
    p->next = NULL;
    labels[index] = p;
}
PROGLIST gotoLabel(char *s) {
    int index;
    index = hashChar(s);
    if(labels[index] == NULL)return NULL;
    LABELIST p = labels[index];
    return p->proglist;
}
