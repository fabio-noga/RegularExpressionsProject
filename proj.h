typedef enum {ATRIB, ADD, SUB, MUL, DIV, IF_I, WRITE, READ, GOTO_I, LABEL, EMP} OpKind;
//Adicionado EMP como EMPTY para que o programa corra na mesma mesmo que encontre linhas inúteis como \n ou não executáveis
typedef enum {EMPTY, FLOAT_CONST, STRING} ElemKind;
//Substituido INT_CONST por FLOAT_CONST para poder fazer divisões
typedef struct elem{
    ElemKind kind;
    union {
        float val;
        char *name;
    } contents;
} Elem;

typedef struct {
    OpKind op;
    Elem first, second, third;
} Instr;

typedef struct proglist {
    Instr instruction;
    struct proglist *next;
} *PROGLIST;


Elem mkVar(char *s);
Elem mkFloat(float n);
Elem empty();
float getValue(Elem x);
char *getName(Elem x);
Instr mkInstr(OpKind oper, Elem x, Elem y, Elem z);
Instr instrType(char *name);
void printVar(Elem x); //Elem tester


//PROGRAM LIST
PROGLIST mkProgList(Instr givenInstr);
PROGLIST addProgLast(char *s,PROGLIST l);
void compileList(PROGLIST l);
void printProgList(PROGLIST l); //List checker


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


//HASH
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
