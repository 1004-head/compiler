#include "hw_table.h"

#define MAXTABLE 100		
#define MAXNAME  31		
#define MAXLEVEL 5	

typedef struct symbol{
    KindT type;
    char name[MAXNAME];
    int val;
    int level;
    int addr;
}Symbol;

Symbol symbolTable[MAXTABLE];
int tIndex=0;
int cLevel=-1;
int localAddr=0;

void blockBegin(int firstAddr)	
{
    if(cLevel==-1){
        tIndex=0;
    }
    localAddr=0;
    cLevel++;

    return;
}

void blockEnd()				
{
    cLevel--;
    return ;
}

int enterTfunc(char *id, int v)		
{
    strcpy(symbolTable[tIndex].name, id);
    symbolTable[tIndex].type = funcId;
    symbolTable[tIndex].val = v;
    return tIndex++;
}

int enterTpar(char *id)				
{
    strcpy(symbolTable[tIndex].name, id);
    symbolTable[tIndex].type = parId;
    return tIndex++;
}

int enterTvar(char *id)			
{
	strcpy(symbolTable[tIndex].name, id);
	symbolTable[tIndex].type = varId;
	return tIndex++;
}

int enterTconst(char *id, int v)		
{
    strcpy(symbolTable[tIndex].name, id);
    symbolTable[tIndex].type = constId;
    symbolTable[tIndex].val = v;
    return tIndex++;
}

int searchT(char *id, KindT k)		
{
	for(int i=0; i<tIndex; i++){
		if(!(symbolTable[i].name == id) || !(symbolTable[i].type == k)){
			printf("undef\nCan't find symbol (%s, %s) in the table\n", symbolTable[i].name, symbolTable[i].type);
			return -1;
		}
		printf("Index : %d\t\tkind : %s\t\tId : %s\n", i, symbolTable[i].type, symbolTable[i].name);
	}
	return 0;
}

void printTable() 
{
	printf("Index\tkindT\tname\tvalue\tlevel\taddr\tpars\n");
	for(int i=0; i<tIndex; i++){
		printf("[%d]\t%s\t%s\t%d\t%d\t%d\t%d\n",i, symbolTable[i].type,
				symbolTable[i].name, symbolTable[i].val, 
				symbolTable[i].level, symbolTable[i].addr, 
				symbolTable[i].val);
	}
}
