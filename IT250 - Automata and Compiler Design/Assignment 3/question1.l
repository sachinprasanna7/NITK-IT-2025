%{
#include <stdio.h>
int n;
int accepted = 0;
int rejected = 0;
%}

%%

[01]+ {
    int zeroCount = 0, oneCount = 0;
    for (int i = 0; i < yyleng; i++) {
        if (yytext[i] == '0') {
            zeroCount++;
        }
        else oneCount++;
    }
    if (oneCount % 2 == 1 && zeroCount % 2 == 0) {
        printf("A ");
        accepted++;
    }
    else {
        printf("R ");
        rejected++;
    }
}

.* {printf("I ");}

%%


int yywrap(void){
    return 1;
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char input[100];
        scanf("%s", input);
        yy_scan_string(input);
        yylex();
    }
    printf("\n");
    printf("%d %d", accepted, rejected);
    printf("\n");
    return 0;
}