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
    int pars;
}Symbol;

Symbol symbolTable[MAXTABLE];
int tIndex=0;
int cLevel=-1;
int localAddr=0;
int funcAddr=0;
int parAddr=0;

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
    symbolTable[tIndex].level = cLevel;
    symbolTable[tIndex].addr = funcAddr++;
    symbolTable[tIndex].pars = v;
    parAddr = -1*v;
    return tIndex++;
}

int enterTpar(char *id)				
{
    strcpy(symbolTable[tIndex].name, id);
    symbolTable[tIndex].type = parId;
    symbolTable[tIndex].level = cLevel;
    symbolTable[tIndex].addr = ++localAddr;
    return tIndex++;
}

int enterTvar(char *id)			
{
	strcpy(symbolTable[tIndex].name, id);
	symbolTable[tIndex].type = varId;
  symbolTable[tIndex].level = cLevel;
  symbolTable[tIndex].addr = ++localAddr;
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
		if(!(symbolTable[i].name == id)){
      switch(k){
        case varId:
			    printf("undef\nCan't find symbol (%s, var) in the table\n", symbolTable[i].name);
          break;
        case parId:
			    printf("undef\nCan't find symbol (%s, par) in the table\n", symbolTable[i].name);
          break;
        case constId:
			    printf("undef\nCan't find symbol (%s, const) in the table\n", symbolTable[i].name);
          break;
        default:
          continue;
      }
			return -1;
		}
    switch(k){
      case varId:
		    printf("Index : %d\t\tkind : var\t\tId : %s\n", i, symbolTable[i].name);
        break;
      case parId:
		    printf("Index : %d\t\tkind : par\t\tId : %s\n", i, symbolTable[i].name);
        break;
      case constId:
		    printf("Index : %d\t\tkind : const\t\tId : %s\n", i, symbolTable[i].name);
        break;
      default:
			  printf("undef\nCan't find symbol (%s, %s) in the table\n", symbolTable[i].name, symbolTable[i].type);
    }
	}
	return 0;
}

void printTable() 
{
	printf("Index\tkindT\tname\tvalue\tlevel\taddr\tpars\n");
	for(int i=0; i<tIndex; i++){
    KindT k = symbolTable[i].type;
    switch(k){
      case varId:
		    printf("[%d]\tvar\t%s\t\t\t%d\t%d\t\t\n",i, symbolTable[i].name,
        symbolTable[i].level, symbolTable[i].addr);
        break;
      case funcId:
		    printf("[%d]\tfunc\t%s\t\t\t%d\t%d\t%d\n",i, symbolTable[i].name,
        symbolTable[i].level, symbolTable[i].addr, symbolTable[i].pars);
        break;
      case parId:
		    printf("[%d]\tpar\t%s\t\t\t%d\t%d\t\t\n",i, symbolTable[i].name,
        symbolTable[i].level, symbolTable[i].addr);
        break;
      case constId:
		    printf("[%d]\tconst\t%s\t\t\t\t\t\t\n",i, symbolTable[i].name,
        symbolTable[i].val);
    default:
        continue;
    }
	}
}
