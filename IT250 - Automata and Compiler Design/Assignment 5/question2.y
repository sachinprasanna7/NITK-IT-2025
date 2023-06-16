%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    int yylex(void);
    int yyerror(char *msg);
    int findPower(int, int);
    char password[100] = "";
    int i=0;
%}


%token NUMBER

%left '+' '-'
%left '*' '/' '%'
%left '^'


%%

Statement:  Expression {printf("\n%d\n%s_%d\n\n", $$, password, $$);}
    ;


Expression:      Expression '+' Expression {printf("+"); $$ = $1 + $3; password[i++] = '+';}

    |   Expression '*' Expression {printf("*");$$ = $1 * $3; password[i++] = '*';}
    |   Expression '-' Expression {printf("-");$$ = $1 - $3; password[i++] = '-';}
    |   Expression '/' Expression {printf("/");
        if($3 == 0){
            printf("Division by Zero!!");
            exit(0);
        }
        $$ = $1 / $3; password[i++] = '/';}
    |   Expression '%' Expression {printf("%%");$$ = $1 % $3; password[i++] = '%';}
    |   Expression '^' Expression {printf("^");$$ = $1^$3; password[i++] = '^';}
    |   '(' Expression ')' {$$ = $2; }


    |   NUMBER     {printf("%d", yylval);

            //Append each digit to the password by this method, traversing through the number

            int temp = yylval;
            int count = 0;

            // Counting number of digits
            while (temp > 0) {
                count++;
                temp /= 10;
            }

            // Main loop, to add each digit
            while (count > 0) {
                int digit = (yylval / findPower(10, count-1)) % 10;
                password[i++] = (char)(digit + 48);
                count--;
        }}

      
    
     
    | error { exit(0); }
    ;
%%


int main(){
    yyparse();
}

int findPower(int a, int b){
    int result = 1;
    for(int i=0; i<b; i++){
        result *= a;
    }
    return result;
}

int yyerror (char *msg) {
    return printf ("\nInvalid Expression\n");
}