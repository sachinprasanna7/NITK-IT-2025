%{
  #include <stdio.h>
  #include <stdlib.h>
  int yylex(void);
  void yyerror(char *msg);
%}
 
%token ID NUMBER

//Operator Associativity

%left '+' '-'
%left '*' '/' '%'
%left '^'


%%
Statement : Expression    { printf("Valid\n%d\n\n", $$); return 0;}
 
Expression :
    Expression '+' Expression { $$ = $1 + $3; }
    | Expression '-' Expression { $$ = $1 - $3; }
    | Expression '*' Expression { $$ = $1 * $3; }
    | Expression '/' Expression { $$ = $1 / $3;
      if($3 == 0){
            printf("Division by Zero!!");
            exit(0);
        }}
    | Expression '%' Expression { $$ = $1 % $3; }
    | Expression '^' Expression { $$ = $1 ^ $3; }
    | '-' ID { $$ = -$2; }
    | '-' NUMBER { $$ = -$2; }
    | '(' Expression ')' { $$ = $2; }
    | ID { $$ = $1;}
    | NUMBER { $$ = $1;}
    | error { exit(0);}
    ;
%%
 
int main() {
    yyparse();
}

void yyerror(char *msg) {
    printf("Invalid\n\n");
}

