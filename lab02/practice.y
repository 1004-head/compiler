%union{
	char *name;
	int val;
}
%{
    #include <stdio.h>
    int yylex();
    void yyerror();
%}

%token COLOEQ EQ NOTEQ LE LT GE GT
%token CONST VAR FUNCTION BEGINN END IF THEN WHILE DO RETURN WRITE WRITELN ODD
%token IDENT
%token NUMBER

%%
program: block '.' { printf("program -> block .\n"); }
;
block: declList statement { printf("block -> declList statement\n"); }
;
declList:
| declList decl { printf("declList -> declList decl\n"); }
;
decl: constDecl { printf("decl -> constDecl\n"); }
| varDecl { printf("decl -> varDecl\n"); }
| funcDecl { printf("decl -> funcDecl\n"); }
;
constDecl: CONST numberList ';' { printf("constDecl -> CONST numberList ;\n"); }
;
numberList: IDENT EQ NUMBER { printf("numberList -> IDENT EQ NUMBER\n"); }
| numberList COMMA IDENT EQ NUMBER { printf("numberList -> COMMA IDENT EQ NUMBER\n"); }
;
varDecl: VAR identList ';' { printf("varDecl -> VAR identList ;\n"); }
;
identList: IDENT { printf("identList -> IDENT\n"); }
| identList COMMA IDENT { printf("identList -> ident COMMA IDENT\n"); }
;
optParList:
| parList { printf("optParList -> parList\n"); }
;
parList: IDENT { printf("parList -> IDENT\n"); }
| parList COMMA IDENT { printf("parList -> parList COMMA IDENT\n"); }
;
funcDecl: FUNCTION IDENT '(' optParList ')' block ';' { printf("funcDecl -> FUNCTION IDENT ( optParList ) block ;\n"); }
;
statement:
| IDENT COLOEQ expression { printf("statement -> IDENT COLOEQ expression\n"); }
| BEGINN statement stateList END { printf("statement -> BEGINN statement stateList END\n"); }
| IF condition THEN statement { printf("statement -> IF condition THEN statement\n"); }
| WHILE condition DO statement { printf("statement -> WHILE condition DO statement\n"); }
| RETURN expression { printf("statement -> RETURN expression\n"); }
| WRITE expression { printf("statement -> WRITE expression\n"); }
| WRITELN { printf("statement -> WRITELN\n"); }
;
stateList:
| stateList ';' statement { printf("stateList -> stateList ; statement"); }
;
condition: ODD expression { printf("condition -> ODD expression\n"); }
| expression EQ expression { printf("condition -> expression EQ expression\n"); }
| expression NOTEQ expression { printf("condition -> expression NOTEQ expression\n"); }
| expression LT expression { printf("condition -> expression LT expression\n"); }
| expression GT expression { printf("condition -> expression GT expression\n"); }
| expression LE expression { printf("condition -> expression LE expression\n"); }
| expression GE expression { printf("condition -> expression GE expression\n"); }
;
expression: '-' term termList { printf("expression -> - term termList\n"); }
| term termList { printf("expression -> term termList\n"); }
;
termList:
| termList '+' term { printf("termList -> termList + term\n"); }
| termList '-' term { printf("termList -> termList - term\n"); }
;
term: factor factList { printf("term -> factor factList\n"); }
;
factList:
| factList '*' factor { printf("factList -> factList * factor\n"); }
| factList '/' factor { printf("factList -> factList / factor\n"); }
;
factor: IDENT { printf("factor -> IDENT\n"); }
| NUMBER { printf("factor -> NUMBER\n"); }
| IDENT '(' expList ')' { printf("factor -> IDENT ( expList )\n"); }
| '(' expression ')' { printf("factor -> ( expression )\n"); }
;
expList: expression { printf("expList -> expression\n"); }
| expList ',' expression { printf("expList -> expList , expression\n"); }
;
COMMA: ',' { printf("comma -> ,\n"); }
;
%%

int main(int argc, char *argv[]){
    yyparse();
}

void yyerror(char *s){
    fprintf(stderr, "errors: %s\n", s);
}
