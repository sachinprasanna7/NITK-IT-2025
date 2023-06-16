%{  
 #include<stdio.h>  
 #include<stdlib.h>  
 int yylex();
 int yyerror();
%}  

%token END
%token ID NUM IF ELSE LE GE EQ NE OR AND STMT KEY LT GT
%right '='
%left AND OR
%left '<' '>' LE GE EQ NE
%left '+''-'
%left '*''/'
%left '!'

%%  

S : STS END {printf("\nParsing is Successful\n\n");  exit(0);}
  ;

STS:    IBLK 
       | STS IBLK 
       ;

IBLK: IF '(' COND ')'  '{' BODY '}' EBLK
      | IF '(' COND ')'  EXPR 
      | IF '(' COND ')'  '{' BODY '}' 
      ;

BODY: IBLK EXPR  
      | IBLK
      | EXPR IBLK
      | EXPR 
      ;

EBLK: ELSE EXPR
        | ELSE '{' BODY '}'
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

EXPR :   STMT



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