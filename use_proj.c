#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj.h"
void main(int argc, char *argv[]) {
    initHash();
    PROGLIST l;
    clearLabelList();
    if(argv[1] != NULL) {
        l = readFile(argv[1]);     
    } else {
        l = readStdin();
        printf("\n###############\n\n");
    }
    initLabelist(l);
    //printProgList(l);
    //printLabelist();
    compileList(l);
}