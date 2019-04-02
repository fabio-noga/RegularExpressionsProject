typedef enum {ATRIB, ADD, SUB, MUL, DIV, IF_I, WRITE, READ, GOTO_I, LABEL,EMP} OpKind;

typedef enum {EMPTY, FLOAT_CONST, STRING} ElemKind;

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
Instr mkInstr(OpKind oper, Elem x, Elem y, Elem z);
Instr instrType(char *name);
void printVar(Elem x);

/*typedef struct proglist {
	char *name;
    struct proglist *next;
} *PROGLIST;
*/
typedef struct labelist {
	char *name;
	PROGLIST proglist;
    struct labelist *next;
} *LABELIST;

#define LABELMAX 100000
LABELIST labels[LABELMAX];
void initLabelist(PROGLIST l);
void insertLabel(char *s, PROGLIST l);
PROGLIST gotoLabel(char *s);
void printLabelist();


PROGLIST mkProgList(Instr givenInstr);
PROGLIST addProgLast(char *s,PROGLIST l);
void printProgList(PROGLIST l);
void compileList(PROGLIST l);

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
