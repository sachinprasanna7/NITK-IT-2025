%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int mini = -1;  
%}

%%

([a-b]*[^a-b \n\t]+[a-b]*)+ {
    printf("-1 ");   
}

(a(ba)*b?|b(ab)*a?) { 
    if(mini == -1) mini = yyleng;
    else if (yyleng < mini) {
        mini = yyleng;
    }
    printf("valid ");    
}

[ab]* {
    if(mini == -1) mini = yyleng;
    else if (yyleng < mini) {
        mini = yyleng;
    }
    printf("invalid ");   
}

[\n] { printf("\n%d\n", mini);}
    
    return 0;
}

%%
int yywrap()
{
    return 1;
}

int main()
{    
    yylex();   
    return 0;
}