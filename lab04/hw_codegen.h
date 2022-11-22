#define MAXCODE

typedef enum codes{
    lit, opr, lod, sto, ict, ret, jmp
}OpCode;

typedef enum ops{
    wrt, wrl
}Operator;

typedef struct inst{
    OpCode opCode;
    union{
        RelAddr addr;
        int value;
        Operator optr;
    }u;
}Inst;

static Inst code[MAXCODE];
static int cIndex = -1;

int genCodeV(OpCode op, int v);		
int genCodeT(OpCode op, int ti);
int genCodeO(Operator p);	
int genCodeR();			
void backPatch(int i);

int nextCode();		
void listCode();
void execute();


