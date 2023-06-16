%{
#include <stdio.h>
#include <string.h>
int n;
int matches = 0;
char K[11];
%}

%%

[a-zA-Z_]+ {
    if (strstr(yytext, K) != NULL) {
        matches++;
    }
}

.* {}

%%
int yywrap(void){
    return 1;
}

int main() {

    scanf("%d", &n);
    scanf("%s", K);

    for (int i = 0; i < n; i++) {
        char input[1000];
        scanf("%s", input);
        yy_scan_string(input);
        yylex();
    }

    printf("\n%d\n\n", matches);

    return 0;
}