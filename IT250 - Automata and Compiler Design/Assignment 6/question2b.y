%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyparse();
%}

%token END
%token ID NUM WHILE LE GE EQ NE OR AND STMT OP CP DO KEY LT GT
%right '='
%left AND OR
%left '<' '>' LE GE EQ NE
%left '+''-'
%left '*''/'
%left '!'

%%

S : WHILEBLOCKS END {printf("Parsed\n");
return 0;}
   | DOWHILEBLOCK END {printf("Parsed\n"); return 0;}
   ;

DOWHILEBLOCK: DO '{' WHILEBODY '}' WHILESTATEMENT ';' {}
            ;



WHILEBLOCKS: WHILEBLOCK {}
            | WHILEBLOCKS WHILEBLOCK {}
            ;

WHILEBLOCK: WHILESTATEMENT '{' WHILEBODY '}' {}
        | WHILESTATEMENT ';' {}
        | WHILESTATEMENT STMT ';' {}
        | WHILESTATEMENT WHILEBLOCK {}
        ;

WHILESTATEMENT: WHILE OP EXPRESSION CP {}
                ;


WHILEBODY: WHILEBLOCK {}
        |DOWHILEBLOCK {}
        |STMT ';' {}
        |STMT ';' WHILEBLOCK {}
        |STMT ';' WHILEBLOCK STMT ';' {}
        |WHILEBLOCK STMT ';' {}
        |STMT ';' DOWHILEBLOCK {}
        |STMT ';' DOWHILEBLOCK STMT ';' {}
        |DOWHILEBLOCK STMT ';' {}
        ;
        

EXPRESSION: EXPRESSION '+' EXPRESSION {}
        |EXPRESSION '*' EXPRESSION {}
        |EXPRESSION '-' EXPRESSION {}
        |EXPRESSION '/' EXPRESSION {}
        |EXPRESSION '<' EXPRESSION {}
        |EXPRESSION '>' EXPRESSION {}
        |EXPRESSION '=' EXPRESSION {}
        |EXPRESSION OR EXPRESSION {}
        |EXPRESSION AND EXPRESSION {}
        |'!' EXPRESSION {}
        |EXPRESSION GE EXPRESSION {}
        |EXPRESSION EQ EXPRESSION {}
        |EXPRESSION NE EXPRESSION {}
        |EXPRESSION LE EXPRESSION {}
        |OP EXPRESSION CP {}
        |NUM {}
        |ID {}
        ;

%%

int yyerror()
{
    printf("COCK");
    return 0;
}

int main()
{
    yyparse();
    return 0;
}