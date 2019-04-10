#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proglist.h"
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

//String to mkInstr
Instr instrType(char *name) {
    char functionName[255];
    char varName[255], varName2[255];
    int j = 0, i = 0;
    Elem first = empty(), second = empty(), third = empty();
    OpKind op;
    while(name[i] != '(' && name[i] != '\0' && name[i] != ' ' && name[i] != '=' && name[i] != ';') {
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
            printf("Variavel %s inválida\n", varName);
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
        int flag = 0;
        j = 0;
        while(varName[j] != '\0') {
            if(!(varName[j] >= '0' && varName[j] <= '9')) {
                flag = 1;
            }
            j++;
        }
        if(flag == 1) {
            first = mkVar(varName);
        } else first = mkFloat((float)atoi(varName));
        return mkInstr(op, first, empty(), empty());
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
        j = 0;
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
        varName[j] = '\0';
        return mkInstr(op, mkVar(varName), empty(), empty());
    } /*fim*/  else if(strcmp(functionName, "quit") == 0 || strcmp(functionName, "\0") == 0) {
        return mkInstr(EMP, empty(), empty(), empty());
    } else {
        printf("WARNING: Instrução inválida. linha ignorada %s - %s\n", name, functionName);
        return mkInstr(EMP, empty(), empty(), empty());
    }
}