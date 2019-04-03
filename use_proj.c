#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj.h"
int  main(int argc, char *argv[]) {
    initHash();
    PROGLIST l;
    char reader[255];
    for(int i = 0; i < LABELMAX; i++) {
        labels[i] = NULL;
    }
    if(argv[1] != NULL) {
        FILE *fp;
        char ch, file_name[25];
        strcpy(file_name, argv[1]);

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
    } else {
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
        printf("\n###############\n\n");
    }
    initLabelist(l);
    //printProgList(l);
    //printLabelist();
    compileList(l);

}