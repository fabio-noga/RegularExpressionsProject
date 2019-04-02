#include "proj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//




//Program reader
PROGLIST mkProgList(Instr givenInstr) {
    PROGLIST p;
    p = (PROGLIST)malloc(sizeof(struct proglist));
    p->instruction = givenInstr;
    p->next = NULL;
    return p;
}
PROGLIST addProgLast(char *s, PROGLIST l) {
    PROGLIST p = l;
    if(l == NULL)return NULL;
    while((l->next) != NULL)l = l->next;
    l->next = mkProgList(instrType(s));
    return p;
}
Instr instrType(char *name) {
    char functionName[255];
    char varName[255], varName2[255];
    int j = 0, i = 0;
    Elem first = empty(), second = empty(), third = empty();
    OpKind op;
    while(name[i] != '(' && name[i] != '\0' && name[i] != ' ' && name[i] != '=') {
        functionName[i] = name[i];
        i++;
    }
    functionName[i] = '\0';
    first = mkVar(functionName);
    while(name[i] == ' ' && name[i] != '=')i++;
    //Se for uma atribuição
    if(name[i] == '=') {
        op = ATRIB;
        first = mkVar(functionName);
        i++;
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
        if(name[i] == '\0' || name[i] == ';') {
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
                second = mkVar(varName);
            } else second = mkFloat((float)atoi(varName));
            return mkInstr(op, first, second, empty());
        } else {
            switch(name[i]) {
            case '+':
                op = ADD;
                break;
            case '-':
                op = SUB;
                break;
            case '*':
                op = MUL;
                break;
            case '/':
                op = DIV;
                break;
            default:
                printf("Operador %c inexistente\n", name[i]);
                exit(0);
            }
            i++;
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
                second = mkVar(varName);
            } else second = mkFloat((float)atoi(varName));

            flag = 0;
            j = 0;
            while(varName2[j] != '\0') {
                if(!(varName2[j] >= '0' && varName2[j] <= '9')) {
                    flag = 1;
                }
                j++;
            }
            if(flag == 1) {
                third = mkVar(varName2);
            } else third = mkFloat((float)atoi(varName2));
            //printf("feito: %d\n",varVal2);
            return mkInstr(op, first, second, third);
        }
    } /*read*/ else if(strcmp(functionName, "ler") == 0) {
        i++;
        op = READ;
        while(name[i] != ')' && name[i] != '\0') {
            varName[j] = name[i];
            i++;
            j++;
        }
        varName[j] = '\0';
        j = 0;
        int flag = 0;
        while(varName[j] != '\0') {
            if(!(varName[j] >= '0' && varName[j] <= '9')) {
                flag = 1;
            }
            j++;
        }
        if(flag == 0) {
            printf("Variável %s inválida\n", varName);
            exit(0);
        }
        //printf("Valor: %s - %d\n",varName,hashChar(varName));
        return mkInstr(op, mkVar(varName), empty(), empty());
    } /*write*/else if(strcmp(functionName, "escrever") == 0) {
        i++;
        op = WRITE;
        while(name[i] != ')' && name[i] != '\0') {
            varName[j] = name[i];
            i++;
            j++;
        }
        varName[j] = '\0';
        return mkInstr(op, mkVar(varName), empty(), empty());
    } /*if*/   else if(strcmp(functionName, "if") == 0) {
        op = IF_I;
        while(name[i] != '\0' && name[i] != ';' && name[i] != ' ') {
            varName[j] = name[i];
            j++;
            i++;
        }
        varName[j] = '\0';
        if(name[i] == ';' || name[i] == '\0') {
            printf("If Inválido\n");
            exit(0);
        }
        while(name[i] == ' ')i++;
        j = 0;
        while(name[i] != '\0' && name[i] != ';') {
            varName2[j] = name[i];
            j++;
            i++;
        }
        varName2[j] = '\0';
        return mkInstr(op, mkVar(varName), mkVar(varName2), empty());
    } /*goto*/ else if(strcmp(functionName, "goto") == 0) {
        op = GOTO_I;
        j=0;
        while(name[i] != '\0' && name[i] != ' ' && name[i] != ';') {
            varName[j] = name[i];
            j++;
            i++;
        }
        varName[j] = '\0';
        return mkInstr(op, mkVar(varName), empty(), empty());
    } /*label*/else if(strcmp(functionName, "label") == 0) {
        op = LABEL;
        while(name[i] != '\0' && name[i] != ' ' && name[i] != ';') {
            varName[j] = name[i];
            j++;
            i++;
        }
        varName[j] == '\0';
        return mkInstr(op, mkVar(varName), empty(), empty());
    } /*fim*/  else if(strcmp(functionName, "q") == 0 || strcmp(functionName, "\0") == 0) {
        return mkInstr(EMP, empty(), empty(), empty());
    } else {
        printf("WARNING: Instrução inválida. linha ignorada %s - %s\n", name, functionName);
        return mkInstr(EMP, empty(), empty(), empty());
    }
}
void printProgList(PROGLIST l) {
    while((l->next) != NULL) {
        OpKind op = l->instruction.op;
        Elem first = l->instruction.first;
        Elem second = l->instruction.second;
        Elem third = l->instruction.third;
        switch(op) {
        case ATRIB:
            printf("Type: %u | %s=%.0f\n", op, first.contents.name, second.contents.val);
            break;
        case ADD:
            if(second.kind == FLOAT_CONST && third.kind == FLOAT_CONST)printf("Type: %u | %s=%.0f+%0.f\n", op, first.contents.name, second.contents.val, third.contents.val);
            else if(second.kind == STRING && third.kind == FLOAT_CONST)printf("Type: %u | %s=%s+%0.f\n", op, first.contents.name, second.contents.name, third.contents.val);
            else if(third.kind == STRING && second.kind == FLOAT_CONST)printf("Type: %u | %s=%.0f+%s\n", op, first.contents.name, second.contents.val, third.contents.name);
            else printf("Type: %u | %s=%s+%s\n", op, first.contents.name, second.contents.name, third.contents.name);
            break;
        case SUB:
            if(second.kind == FLOAT_CONST && third.kind == FLOAT_CONST)printf("Type: %u | %s=%.0f-%0.f\n", op, first.contents.name, second.contents.val, third.contents.val);
            else if(second.kind == STRING && third.kind == FLOAT_CONST)printf("Type: %u | %s=%s-%0.f\n", op, first.contents.name, second.contents.name, third.contents.val);
            else if(third.kind == STRING && second.kind == FLOAT_CONST)printf("Type: %u | %s=%.0f-%s\n", op, first.contents.name, second.contents.val, third.contents.name);
            else printf("Type: %u | %s=%s-%s\n", op, first.contents.name, second.contents.name, third.contents.name);
            break;
        case MUL:
            if(second.kind == FLOAT_CONST && third.kind == FLOAT_CONST)printf("Type: %u | %s=%.0f*%0.f\n", op, first.contents.name, second.contents.val, third.contents.val);
            else if(second.kind == STRING && third.kind == FLOAT_CONST)printf("Type: %u | %s=%s*%0.f\n", op, first.contents.name, second.contents.name, third.contents.val);
            else if(third.kind == STRING && second.kind == FLOAT_CONST)printf("Type: %u | %s=%.0f*%s\n", op, first.contents.name, second.contents.val, third.contents.name);
            else printf("Type: %u | %s=%s*%s\n", op, first.contents.name, second.contents.name, third.contents.name);
            break;
        case DIV:
            if(second.kind == FLOAT_CONST && third.kind == FLOAT_CONST)printf("Type: %u | %s=%.0f/%0.f\n", op, first.contents.name, second.contents.val, third.contents.val);
            else if(second.kind == STRING && third.kind == FLOAT_CONST)printf("Type: %u | %s=%s/%0.f\n", op, first.contents.name, second.contents.name, third.contents.val);
            else if(third.kind == STRING && second.kind == FLOAT_CONST)printf("Type: %u | %s=%.0f/%s\n", op, first.contents.name, second.contents.val, third.contents.name);
            else printf("Type: %u | %s=%s/%s\n", op, first.contents.name, second.contents.name, third.contents.name);
            break;
        case IF_I:
            printf("Type: %u | if %s!=0 then %s\n", op, first.contents.name, second.contents.name);
            break;
        case WRITE:
            printf("Type: %u | WRITE: %s\n", op, first.contents.name);
            break;
        case READ:
            printf("Type: %u | READ: %s\n", op, first.contents.name);
            break;
        case GOTO_I:
            printf("Type: %u | GOTO_I: %s\n", op, first.contents.name);
            break;
        case LABEL:
            printf("Type: %u | LABEL: %s\n", op, first.contents.name);
            break;
        case EMP:
            printf("Type: %u | EMPTY\n", op);
            break;
        default:
            printf("%u Ainda nada\n", op);
            return;
        }
        l = l->next;
    }
    return;
}

float calculatorAssistant(OpKind op,float val1,float val2){
    switch(op){
        case ADD:return val1+val2;
        case SUB:return val1-val2;
        case MUL:return val1*val2;
        case DIV:return val1/val2;
        default:return -1;
    }
}

void compileList(PROGLIST l) {
    if(l==NULL)return;
    Instr localInstr=l->instruction;
    Elem first= localInstr.first;
    Elem second= localInstr.second;
    Elem third=localInstr.third;
    switch(l->instruction.op){
            case ATRIB:
                if(second.kind==FLOAT_CONST)insertHash(first.contents.name, second);
                else{
                    MAP p = lookupHash(second.contents.name);
                    if(p == NULL) {
                        printf("Variavel %s não declarada\n", second.contents.name);
                        return;
                    } else insertHash(first.contents.name, p->value);
                }
                break;
            case ADD:case SUB:case MUL: case DIV:;
                float val1,val2;
                if(second.kind==STRING){
                    MAP p = lookupHash(second.contents.name);
                    if(p == NULL) {
                        printf("Variavel %s não declarada\n", second.contents.name);
                        return;
                    } else val1=p->value.contents.val;
                }else val1=second.contents.val;
                if(third.kind==STRING){
                    MAP p = lookupHash(third.contents.name);
                    if(p == NULL) {
                        printf("Variavel %s não declarada\n", third.contents.name);
                        return;
                    } else val2=p->value.contents.val;
                }else val2=third.contents.val;
                insertHash(first.contents.name, mkFloat(calculatorAssistant(l->instruction.op,val1,val2)));
                
                break;
            case WRITE:;
                MAP p = lookupHash(first.contents.name);
                if(p == NULL) {
                    printf("Variavel %s não declarada\n", first.contents.name);
                    return;
                } else printf("Variável %s: %.0f\n",first.contents.name,p->value.contents.val);
                break;
            case READ:;
                Elem scan;
                printf("Ler variável %s: ",first.contents.name);
                scanf("%f",&scan.contents.val);
                insertHash(first.contents.name, scan);
                break;
            case IF_I:;
                MAP b = lookupHash(first.contents.name);
                if(b == NULL) {
                    printf("Variavel %s não declarada\n", first.contents.name);
                    return;
                } else if((int)b->value.contents.val!=0){
                    PROGLIST n;
                    n = (PROGLIST)malloc(sizeof(struct proglist));
                    n->instruction=instrType(second.contents.name);
                    n->next=l->next;
                    compileList(n);
                    return;
                }
                break;
            case GOTO_I:;
                PROGLIST lTemp=gotoLabel(first.contents.name);
                if(lTemp==NULL){
                    printf("Label Inexistente\n");
                    return;
                }
                compileList(lTemp);
                return;
            case EMP:case LABEL:break;
            default:printf("empty as my soul");break;
                
    }
    compileList(l->next);
}

void initLabelist(PROGLIST l) {
    while(l!=NULL){
        if(l->instruction.op == LABEL) {
            Elem x=l->instruction.first;
            //printf("Label: %s\n", x.contents.name);
            insertLabel(x.contents.name, l->next);
        }
        l=l->next;
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

void printVar(Elem x) {
    switch(x.kind) {
    default:
        printf("Empty\n");
        break;
    case FLOAT_CONST:
        printf("%.2f\n", x.contents.val);
        break;
    case STRING:
        printf("%s\n", x.contents.name);
        break;
    }
}
Elem mkFloat(float n) {
    Elem e;
    e.kind = FLOAT_CONST;
    e.contents.val = n;
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
Instr mkInstr(OpKind oper, Elem x, Elem y, Elem z) {
    Instr t;
    t.op = oper;
    t.first = x;
    t.second = y;
    t.third = z;
    return t;
}
/*
void readVar(Elem x);

PROGLIST newlist(int x,char *s, PROGLIST l);
int lenght (PROGLIST x);
PROGLIST findLabel(char *s);
PROGLIST addLast(int, PROGLIST);
PROGLIST filter(int (*p)(int), PROGLIST);
float getValue(Elem x);*/


//
