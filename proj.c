#include "proj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Program reader




float calculatorAssistant(OpKind op, float val1, float val2) {
    switch(op) {
    case ADD:
        return val1 + val2;
    case SUB:
        return val1 - val2;
    case MUL:
        return val1 * val2;
    case DIV:
        return val1 / val2;
    default:
        return -1;
    }
}

void compileList(PROGLIST l) {
    if(l == NULL)return;
    Instr localInstr = l->instruction;
    Elem first = localInstr.first;
    Elem second = localInstr.second;
    Elem third = localInstr.third;
    switch(l->instruction.op) {
    case ATRIB:
        if(second.kind == FLOAT_CONST)insertHash(first.contents.name, second);
        else {
            MAP p = lookupHash(second.contents.name);
            if(p == NULL) {
                printf("Variavel %s não declarada\n", second.contents.name);
                return;
            } else insertHash(first.contents.name, p->value);
        }
        break;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
        ;
        float val1, val2;
        if(second.kind == STRING) {
            MAP p = lookupHash(second.contents.name);
            if(p == NULL) {
                printf("Variavel %s não declarada\n", second.contents.name);
                return;
            } else val1 = p->value.contents.val;
        } else val1 = second.contents.val;
        if(third.kind == STRING) {
            MAP p = lookupHash(third.contents.name);
            if(p == NULL) {
                printf("Variavel %s não declarada\n", third.contents.name);
                return;
            } else val2 = p->value.contents.val;
        } else val2 = third.contents.val;
        insertHash(first.contents.name, mkFloat(calculatorAssistant(l->instruction.op, val1, val2)));

        break;
    case WRITE:
        if(first.kind == FLOAT_CONST) printf("Número: %.0f\n", getValue(first));
        else {
            MAP p = lookupHash(getName(first));
            if(p == NULL) {
                printf("Variavel %s não declarada\n", first.contents.name);
                return;
            } else printf("Variavel %s: %.0f\n", first.contents.name, p->value.contents.val);
        }
        break;
    case READ:
        ;
        Elem scan;
        printf("Ler variavel %s: ", getName(first));
        scanf("%f", &scan.contents.val);
        insertHash(getName(first), scan);
        break;
    case IF_I:
        ;
        MAP b = lookupHash(first.contents.name);
        if(b == NULL) {
            printf("Variavel %s não declarada\n", getName(first));
            return;
        } else if((int)b->value.contents.val != 0) {
            PROGLIST n;
            n = (PROGLIST)malloc(sizeof(struct proglist));
            n->instruction = instrType(getName(second));
            n->next = l->next;
            compileList(n);
            return;
        }
        break;
    case GOTO_I:
        ;
        PROGLIST lTemp = gotoLabel(getName(first));
        if(lTemp == NULL) {
            printf("Label Inexistente\n");
            return;
        }
        compileList(lTemp);
        return;
    case EMP:
    case LABEL:
        break;
    default:
        printf("empty as my soul");
        break;

    }
    compileList(l->next);
}



void printVar(Elem x) {
    switch(x.kind) {
    default:
        printf("Empty\n");
        break;
    case FLOAT_CONST:
        printf("%.2f\n", getValue(x));
        break;
    case STRING:
        printf("%s\n", getName(x));
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

Instr mkInstr(OpKind oper, Elem x, Elem y, Elem z) {
    Instr t;
    t.op = oper;
    t.first = x;
    t.second = y;
    t.third = z;
    return t;
}

//Não utilizados em maior parte do código por esquecimento
float getValue(Elem x) {
    return x.contents.val;
}
char *getName(Elem x) {
    return x.contents.name;
}
/*
void readVar(Elem x);                        //Usado apenas como debugger. Utilizado apenas printVar
PROGLIST newlist(int x,char *s, PROGLIST l); //Substituido por mkProgList
PROGLIST addLast(int, PROGLIST);             //Substituido por addProgLast
int lenght (PROGLIST x);                     //Apenas necessário para mostrar quantas linhas de código foram escritas, logo desnecessário
PROGLIST findLabel(char *s);                 //Substituido por gotoLabel já que a lista de labels é uma hashtable
PROGLIST filter(int (*p)(int), PROGLIST);    //Não utilizado
*/

PROGLIST readFile(char *arg) {
    FILE *fp;
    PROGLIST l;
    char ch, file_name[25];
    strcpy(file_name, arg);
    char reader[255];
    fp = fopen(file_name, "r"); // read mode

    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        reader[i] = ch;
        i++;
    }
    reader[i] = '\0';
    //printf("\nReader: %s\n", reader);
    l = mkProgList(instrType(reader));
    i = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if(ch != '\n' && ch != ';') {
            reader[i] = ch;
            i++;
        } else {
            reader[i] = '\0';
            if(strcmp(reader, "quit") == 0) {
                l = addProgLast(reader, l);
                break;
            }
            //printf("\nReader: %s\n", reader);
            l = addProgLast(reader, l);
            i = 0;
        }
    }
    fclose(fp);
    return l;
}
void clearLabelList() {
    for(int i = 0; i < LABELMAX; i++) {
        labels[i] = NULL;
    }
}

PROGLIST readStdin() {
    PROGLIST l;
    char reader[255];
    printf("-> ");
    scanf("%[^\n]", reader);
    getchar();
    l = mkProgList(instrType(reader));
    while(strcmp(reader, "quit;") != 0) {
        reader[0] = '\0';
        printf("-> ");
        scanf("%[^\n]", reader);
        getchar();
        l = addProgLast(reader, l);
    }
}

//Debugger | Print proglist
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
            if(first.kind == FLOAT_CONST)printf("Type: %u | WRITE: %.0f\n", op, getValue(first));
            else printf("Type: %u | WRITE: %s\n", op, getName(first));
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