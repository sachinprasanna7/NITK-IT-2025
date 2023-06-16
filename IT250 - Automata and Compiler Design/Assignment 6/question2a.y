%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyparse();
%}

%token END
%token KEY ID NUM FOR LE GE EQ NE OR AND GT LT STMT
%right '='
%left AND OR
%left '<' '>' LE GE EQ NE
%left '+''-'
%left '*''/'
%left '!'

%%
   
S         : STS END{printf("\nParsing is Successful\n\n"); exit(0);}

STS       : STS ST
          | ST
          ; 

ST        : FOR '(' INIT ';' COND ';' INC ')' DEF
          | FOR '(' INIT ';' COND ';' INC ')' EXPR
          | FOR '(' INIT ';' COND ';' INC ')' ';'

          | FOR '(' INIT ';' COND ';' ')' DEF
          | FOR '(' INIT ';' COND ';' ')' EXPR
          | FOR '(' INIT ';' COND ';' ')' ';'

          | FOR '(' INIT ';' ';' INC ')' DEF
          | FOR '(' INIT ';' ';' INC ')' EXPR
          | FOR '(' INIT ';' ';' INC ')' ';'

          | FOR '(' ';' COND ';' INC ')' DEF
          | FOR '(' ';' COND ';' INC ')' EXPR
          | FOR '(' ';' COND ';' INC ')' ';'

          | FOR '(' INIT ';' ';' ')' DEF
          | FOR '(' INIT ';' ';' ')' EXPR
          | FOR '(' INIT ';' ';' ')' ';'

          | FOR '(' ';' COND ';' ')' DEF
          | FOR '(' ';' COND ';' ')' EXPR
          | FOR '(' ';' COND ';' ')' ';'

          | FOR '(' ';' ';' INC ')' DEF
          | FOR '(' ';' ';' INC ')' EXPR
          | FOR '(' ';' ';' INC ')' ';'

          | FOR '('  ';'  ';'  ')' DEF
          | FOR '('  ';'  ';'  ')' EXPR
          | FOR '('  ';'  ';'  ')' ';'

          ;


DEF    : '{' BODY '}'
        | '{' ST BODY '}'
        | '{' BODY ST '}'
        | '{' '}'
           ;

BODY  :     BODY BODY
           | ST
           | EXPR                  
           ;


INC   :  INC '+' '+'
        | INC '-' '-'
        | INC '=' INC '+' INC
        | INC '=' INC '-' INC
        | INC '=' INC '*' INC
        | INC '=' INC '/' INC
        | INC '=' INC '%' INC
        | ID
        | NUM
        ;


COND  :     COND LE COND
           | COND GE COND
           | COND EQ COND
           | COND NE COND
           | COND OR COND
           | COND LT COND
           | COND GT COND
           | COND AND COND
           | COND '+' COND
           | COND '-' COND
           | COND '*' COND
           | COND '/' COND
           | COND '%' COND
           | '(' COND ')'
           | ID
           | NUM
           ;


INIT  :    INIT INIT '=' INIT
           | INIT '=' INIT
           | NUM
           | ID
           | KEY
           | EXPR
           ;

EXPR  :   STMT

%%


int main() {
    printf("\nEnter the expression:\n\n");
    yyparse();
}

int yyerror(){
    printf("\nParsing is Failed\n\n");
    return 1;
}