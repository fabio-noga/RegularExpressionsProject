#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj.h"
int  main(){
    initHash();
    for(int i = 0; i < LABELMAX; i++) {
        labels[i]=NULL;
    }
	char reader[255];
	scanf("%[^\n]",reader);getchar();
	PROGLIST l=mkProgList(instrType(reader));
	while(strcmp(reader,"q")!=0){
		reader[0]='\0';
		//printf("-> ");
		scanf("%[^\n]",reader);getchar();
		l=addProgLast(reader,l);

	}
	initLabelist(l);
	printf("\n###############\n\n");
	//printProgList(l);
	//printLabelist();
	compileList(l);
}