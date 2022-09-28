%{
	unsigned symbolCount = 0, digitCount = 0, identCount = 0, lineCount = 0;
%}

eol \n
symbol [+\-*/();,\.]
ident [a-zA-Z_][0-9a-zA-Z]*
digit [0-9]
integer {digit}+
eq =
noteq "<>"
lt <
gt >
le "<="
ge ">="
coloeq ":="
const "const"
var "var"
function "function"
begin "begin"
end "end"
if "if"
then "then"
while "while"
do "do"
return "return"
write "write"
writeln "writeln"
odd "odd"

%%
{eq} {printf("EQ : =\n");}
{eol} {lineCount++;}
{noteq} {printf("NOTEQ : <>\n");}
{lt} {printf("LT : <\n");}
{gt} {printf("GT : >\n");}
{le} {printf("LE : <=\n");}
{ge} {printf("GE : >=\n");}
{coloeq} {printf("COLOEQ : :=\n");}
{const} {printf("CONST : const\n");}
{var} {printf("VAR : var\n");}
{function} {printf("FUNCTION : function\n");}
{begin} {printf("BEGIN : begin\n");}
{end} {printf("END : end\n");}
{if} {printf("IF : if\n");}
{then} {printf("THEN : then\n");}
{while} {printf("WHILE : while\n");}
{do} {printf("DO : do\n");}
{return} {printf("RETURN : return\n");}
{write} {printf("WRITE : write\n");}
{writeln} {printf("WRITELN : writeln\n");}
{odd} {printf("ODD : odd\n");}
{ident} {printf("Identifier : %s\n", yytext); identCount++;}
{integer} {printf("Number : %d\n", atoi(yytext)); digitCount++;}
{symbol} {printf("Symbol : %s\n", yytext); symbolCount++;}
%%

int main(){
    yylex();
	printf("symbolCount : %d\n", symbolCount);
	printf("digitCount : %d\n", digitCount);
	printf("identCount : %d\n", identCount);
	printf("lineCount : %d\n", lineCount);
    return 0;
}
