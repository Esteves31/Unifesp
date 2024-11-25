DIGIT	[0-9]
KEYW 	else|if|int|return|void|while
LETTER	[a-zA-Z]
OPAREN	\(
CPAREN 	\)
OKEYS 	\{
CKEYS 	\}
OBRACKT \[
CBRACKT \]
SUM 	\+
SUB 	\-
DIV 	\/
MULT 	\*
NQ 	!=
BT 	\>
BTE 	\>=
LT 	\<
LTE 	\<=
EQ 	==
SMC 	;
COMMA 	,
ATRIB 	=

%%

{KEYW}			printf("KEYW");
{DIGIT}{DIGIT}*		printf("NUM");
{LETTER}{LETTER}* 	printf("ID");
{OPAREN}		printf("OPAREN");
{CPAREN}		printf("CPAREN");
{OKEYS}			printf("OKEYS");
{CKEYS}			printf("CKEYS");
{OBRACKT}		printf("OBRACKT");
{CBRACKT}		printf("CBRACKT");
{SUM}			printf("SUM");
{SUB}			printf("SUB");
{MULT}			printf("MULT");
{DIV}			printf("DIV");
{BT}			printf("BT");
{BTE}			printf("BTE");
{LT}			printf("LT");
{LTE}			printf("LTE");
{EQ}			printf("EQ");
{SMC}			printf("SMC");
{COMMA}			printf("COMMA");
{ATRIB}			printf("ATRIB");
{NQ}			printf("NQ");
<<EOF>>			return 0;

%%

int main(int argc, char *argv[]) {
    FILE *f_in;
    if (argc == 2) {
        if (f_in = fopen(argv[1], "r")) {
            yyin = f_in;
        } else {
            perror(argv[0]);
        }
    } else {
        yyin = stdin;
    }
    yylex();
    return 0;
}
