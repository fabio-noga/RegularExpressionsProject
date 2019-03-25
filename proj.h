typedef enum {ATRIB, ADD, SUB, MUL, DIV, IF_I, PRINT, READ, GOTO_I, LABEL} OpKind;

typedef enum {EMPTY, INT_CONST, FLOAT_CONST, STRING} ElemKind;

typedef struct elem{
    ElemKind kind;
    union {
        int val;
        float valS;
        char *name;
    } contents;
} Elem;

typedef struct {
    OpKind op;
    Elem first, second, third;
} Instr;

Elem mkVar(char *s);
Elem mkInt(int n);
Elem mkFloat(float n);
Instr mkInstr(OpKind oper, Elem x, Elem y, Elem z);
void printVar(Elem x);
void readVar(Elem x);
void gotoLabel(char *s);

typedef struct compilelist {
	Instr name;
    struct compilelist *next;
} *COMPILELIST;

typedef struct proglist {
	char *name;
    struct proglist *next;
} *PROGLIST;

typedef struct labelist {
	char *name;
	PROGLIST proglist;
    struct labelist *next;
} *LABELIST;

#define LABELMAX 100000
LABELIST labels[LABELMAX];
void initLabelist(PROGLIST l);
void insertLabel(char *s, PROGLIST l);
PROGLIST findGoto(char *s);
void printLabelist();


PROGLIST mkProgList(char *s,PROGLIST tail);
PROGLIST addProgLast(char *s,PROGLIST l);
void printProgList(PROGLIST);
void createCompiled(PROGLIST);

PROGLIST newlist(int x,char *s, PROGLIST l);
int lenght (PROGLIST x);
PROGLIST findLabel(char *s);
PROGLIST addLast(int, PROGLIST);
PROGLIST filter(int (*p)(int), PROGLIST);
Elem empty();
float getValue(Elem x);

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
