#include "proj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*LIST addLast(int n, LIST l) {
    LIST l2 = l;
    if(l == NULL)return NULL;
    while((l->next) != NULL)l = l->next;
    l->next = newlist(n, NULL);
    return l2;
}

LIST newlist(int n, LIST l) {
    LIST new = malloc(sizeof(struct list));
    new->elem = n;
    new->next = l;
    return new;
}*/
//Program reader
PROGLIST mkProgList(char *s, PROGLIST tail) {
    PROGLIST p;
    p = (PROGLIST)malloc(sizeof(struct proglist));
    p->name = strdup(s);
    p->next = tail;
    return p;
}
PROGLIST addProgLast(char *s, PROGLIST l) {
    PROGLIST p = l;
    if(l == NULL)return NULL;
    while((l->next) != NULL)l = l->next;
    l->next = mkProgList(s, NULL);
    return p;
}
void printProgList(PROGLIST l) {
    while((l->next) != NULL) {
        printf("%s\n", l->name);
        l = l->next;
    }
    return;
}
//program compiler;
void createCompiled(PROGLIST l) {
    if(l->next == NULL)return;
    char *name = l->name;
    char functionName[255];
    int i = 0, equalFlag = 0;
    while(name[i] != '\0') {
        if(name[i] == '=') {
            equalFlag = 1;
            break;
        }
        i++;
    }
    i = 0;
    while(name[i] != '(' && name[i] != '\0' && name[i] != ' ' && name[i] != '=') {
        functionName[i] = name[i];
        i++;
    }
    functionName[i] = '\0';
    //printf("%s\n", name);
    int varPosition = 0, j = 0;
    char varName[255], varName2[255];
    if(name[i] == '(')varPosition = i + 1;
    //Ler Variveis
    if(strcmp(functionName, "ler") == 0) {
        while(name[varPosition] != ')' && name[varPosition] != '\0') {
            varName[j] = name[varPosition];
            varPosition++;
            j++;
        }
        varName[j] = '\0';
        //printf("Valor: %s - %d\n",varName,hashChar(varName));
        printf("Valor de %s: \n-> ", varName);
        float varVal;
        scanf("%f", &varVal);
        insertHash(varName, mkFloat(varVal));
        //escrever variaveis
    } else if(strcmp(functionName, "escrever") == 0) {
        while(name[varPosition] != ')' && name[varPosition] != '\0') {
            varName[j] = name[varPosition];
            varPosition++;
            j++;
        }
        varName[j] = '\0';
        //printf("Valor: %s - %d\n", varName, hashChar(varName));
        MAP p = lookupHash(varName);
        if(lookupHash(varName) == NULL) {
            printf("Variavel %s não declarada\n", varName);
            return;
        } else {
            Elem temp = p->value;
            printf("Valor da Variável %s: ", varName);
            printVar(temp);
        }
    } else if(strcmp(functionName, "goto") == 0) {
        while(name[i] == ' ')i++;
        while(name[i] != '\0' && name[i] != ' ' && name[i] != ';') {
            varName[j] = name[i];
            j++;
            i++;
        }
        PROGLIST p = findGoto(varName);
        if(p == NULL) {
            printf("Label %s não existente\n", varName);
            return;
        }
        //printf("goto\n");
        createCompiled(p);
        return;
    } else if(strcmp(functionName, "if") == 0) {
        while(name[i] == ' ')i++;
        while(name[i] != '\0' && name[i] != ';' && name[i] != ' ') {
            varName[j] = name[i];
            j++;
            i++;
        }
        varName[j]='\0';
        if(name[i] == ';') {
            printf("If Inválido\n");
            return;
        }

        while(name[i] == ' ')i++;
        j=0;
        while(name[i] != '\0' && name[i] != ';') {
            varName2[j] = name[i];
            j++;
            i++;
        }
        varName2[j]='\0';
        //printf("Variavel do if :%s\n", varName);
        MAP p = lookupHash(varName);
        int x;
        if(lookupHash(varName) == NULL) {
            printf("Variavel %s não declarada\n", varName);
            return;
        } else {
            Elem temp = p->value;
            //printf("Valor da Variável %s: ", varName);
            if(temp.contents.valS !=0) {
                //printf("%d\n", (int)temp.contents.valS);
                PROGLIST p = l;
                p->name = varName2;
                createCompiled(p);
                return;
            }
        }

    } else if(equalFlag == 1) {
        while(name[i] == ' ' && name[i] != '=')i++;
        if(name[i] == '=')i++;
        //Dividir os componentes
        while(name[i] == ' ')i++;
        while(name[i] != '\0' && name[i] != ';' && name[i] != ' ' && name[i] != '+' && name[i] != '-' && name[i] != '*' && name[i] != '/') {
            varName[j] = name[i];
            j++;
            i++;
        }
        varName[j] = '\0';
        while(name[i] == ' ')i++;
        //printf("lelel %s - %c\n",varName,name[i]);
        if(name[i] == '\0' || name[i]==';') {
            int flag = 0;
            float varVal;
            j = 0;
            while(varName[j] != '\0') {
                if(!(varName[j] >= '0' && varName[j] <= '9')) {
                    flag = 1;
                }
                j++;
            }
            if(flag == 1) {
                MAP p = lookupHash(varName);
                if(lookupHash(varName) == NULL) {
                    printf("Variavel %s não declarada\n", varName);
                    return;
                } else {
                    Elem temp = p->value;
                    varVal = temp.contents.valS;
                }
            } else varVal = atoi(varName);
            //printf("varval %.2f\n",varVal);
            insertHash(functionName, mkFloat(varVal));
        } else {
            char op = name[i];
            i++;
            //printf("op: %c %s %s\n", op, varName, varName2);
            j = 0;
            while(name[i] == ' ')i++;
            while(name[i] != '\0' && name[i] != ' ' && name[i] != ';') {
                varName2[j] = name[i];
                j++;
                i++;
            }
            varName2[j] = '\0';
            //printf("%s = %s %c %s", functionName, varName, op, varName2);
            //Verificações para o primeiro
            j = 0;
            int flag = 0;
            float varVal, varVal2;
            while(varName[j] != '\0') {
                if(!(varName[j] >= '0' && varName[j] <= '9')) {
                    flag = 1;
                }
                j++;
            }
            if(flag == 1) {
                MAP p = lookupHash(varName);
                if(lookupHash(varName) == NULL) {
                    printf("Variavel %s não declarada\n", varName);
                    return;
                } else {
                    Elem temp = p->value;
                    varVal = temp.contents.valS;
                }
            } else varVal = atoi(varName);

            flag = 0;
            j = 0;
            while(varName2[j] != '\0') {
                if(!(varName2[j] >= '0' && varName2[j] <= '9')) {
                    flag = 1;
                }
                j++;
            }
            if(flag == 1) {
                MAP p2 = lookupHash(varName2);
                if(lookupHash(varName2) == NULL) {
                    printf("Variavel %s não declarada\n", varName2);
                    return;
                } else {
                    Elem temp2 = p2->value;
                    varVal2 = temp2.contents.valS;
                }
            } else varVal2 = atoi(varName2);
            //printf("feito: %d\n",varVal2);

            MAP p3 = lookupHash(functionName);
            float total;
            switch(op) {
            case '+':
                total = varVal + varVal2;
                break;
            case '-':
                total = varVal - varVal2;
                break;
            case '*':
                total = varVal * varVal2;
                break;
            case '/':
                total = varVal / varVal2;
                break;
            default:
                printf("Operador %c inexistente\n", op);
                return;

            }
            insertHash(functionName, mkFloat(total));
        }
    } else {
        //printf("Linha inválida? %s\n", name);
    }
    //printf("\n%s - %s - %s\n", name, varName, functionName);
    createCompiled(l->next);

}
void initLabelist(PROGLIST l) {
    if(l->next == NULL)return;
    char *name = l->name;
    char functionName[255];
    int i = 0, equalFlag = 0;
    while(name[i] != '\0' && name[i] != ' ') {
        functionName[i] = name[i];
        i++;
    }
    functionName[i] = '\0';
    //printf("%s\n", name);
    int varPosition = 0, j = 0;
    char varName[255], varName2[255];
    if(strcmp(functionName, "label") == 0) {
        while(name[i] == ' ')i++;
        while(name[i] != '\0' && name[i] != ' ' && name[i] != ';') {
            varName[j] = name[i];
            j++;
            i++;
        }
        printf("Label: %s\n", varName);
        insertLabel(varName, l->next);
    }
    initLabelist(l->next);
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
PROGLIST findGoto(char *s) {
    int index;
    index = hashChar(s);
    if(labels[index] == NULL)return NULL;
    LABELIST p = labels[index];
    return p->proglist;
}

void printVar(Elem x) {
    switch(x.kind) {
    default:
        printf("Empty\n");
        break;
    case INT_CONST:
        printf("%d\n", x.contents.val);
        break;
    case FLOAT_CONST:
        printf("%.2f\n", x.contents.valS);
        break;
    case STRING:
        printf("%s\n", x.contents.name);
        break;
    }
}
Elem mkInt(int n) {
    Elem e;
    e.kind = INT_CONST;
    e.contents.val = n;
    return e;
}
Elem mkFloat(float n) {
    Elem e;
    e.kind = FLOAT_CONST;
    e.contents.valS = n;
    return e;
}
Elem mkVar(char *s) {
    Elem e;
    e.kind = STRING;
    e.contents.name = strdup(s);
    return e;
}
Elem empty() {
    Elem e;
    e.kind = EMPTY;
    return e;
}

//HASH
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
/*
getVal()
Instr mkInstr(Opkind oper, Elem x, Elem y, Elem z);
void printVar(Elem x);
void readVar(Elem x);
void gotoLabel(char *s);

LABELIST initLabelList(int x, char *s, PROGLIST l);
int lenght (PROGLIST x);
PROGLIST findLabel(char *s);
PROGLIST addLast(int, PROGLIST);
PROGLIST filter(int (*p)(int), PROGLIST);*/



//
