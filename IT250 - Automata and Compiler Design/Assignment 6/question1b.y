%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex();
    int yyerror();
%}

%token END
%token ID NUM SWITCH CASE DEFAULT BREAK LE GE EQ NE OR AND STMT LT GT
%right '='
%left AND OR
%left '<' '>' LE GE EQ NE
%left '+''-'
%left '*''/'
%left '!'

%%

S       :SWITCHSTMT END {printf("\nParsing is Successful\n\n"); exit (0);}
        ;

SWITCHSTMT      :SS '{' BODY '}'
        |SWITCHSTMT SS '{' BODY '}'
        ;

BODY    : CASEBLK 
        | CASEBLKD 
        ;


SS      :SWITCH '(' COND ')'
        ;

CASEBLKD     :CASEBLK D 
        |CASEBLKD CASESTRT 
        |D 
        ;

CASEBLK      :CASESTRT
        |CASEBLK CASESTRT
        ;

D       :DEFAULT ':' INCASE 
        |DEFAULT ':' 
        ;

INCASE      : EXPR 
        |INCASE BREAK ';' 
        |BREAK ';' 
        ;

CASESTRT       :CASE NUM ':' INCASE 
        |CASE NUM ':' 
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
           | '!' COND
           | '(' COND ')'
           | ID
           | NUM
           ;

EXPR :    STMT


%%

int main()
{
    
    printf("\nEnter the expression:\n\n");
    yyparse();
    return 0;
}

int yyerror()
{
    printf("\nParsing is Failed\n\n");
    return 0;
}
