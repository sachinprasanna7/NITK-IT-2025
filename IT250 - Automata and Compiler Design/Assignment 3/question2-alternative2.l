%{
#include <stdio.h>
#include <string.h>
int n;
int mini = -1;
%}

%%

[ab]+ {
    int count = 0;
    int flag = 0;
    char prev = yytext[0];
    for (int i = 1; i < yyleng; i++) {
        if(yytext[i] == prev) flag = 1;
        else prev = yytext[i];
    }
   
    if(flag){
        printf("invalid ");
    }

    else{
        printf("valid ");
        if(mini == -1) mini = yyleng;
        else{
            if(yyleng < mini) mini = yyleng;
        }
    }
}

[ ]+ {}

.* {printf("-1");}

%%


int yywrap(void){
    return 1;
}

int main(){

     while(1){
    char input[100];
    if (scanf("%99s", input) == EOF) break; // Exit loop on end-of-file
    yy_scan_string(input);
    yylex();
    printf(" ");
    //if (scanf("%s", input) == EOF) 
    printf("%d ", mini);
}
    printf("\n");
    printf("%d ", mini);
    printf("\n");
    return 0;
}