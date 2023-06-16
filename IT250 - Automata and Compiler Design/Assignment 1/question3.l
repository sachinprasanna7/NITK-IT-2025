%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
int arr[100000];
int arrsize = 0;
int ctr = 0;
%}

%option noyywrap

%%

[ \t]+              
[0-9]+              {arr[ctr++] = atoi(yytext); }
\n                  {break; }
.                   { printf("Invalid\n"); exit(1); }

%%

int main(){
    char buffer1[1024];
    fgets(buffer1, sizeof(buffer1), stdin);
    if (sscanf(buffer1, "%d", &arrsize) != 1 || arrsize <= 0 || arrsize > 100000 || buffer1[strspn(buffer1, "0123456789 \t\n")] != '\0') {
        printf("Invalid\n");
        exit(1);
    }
    fgets(buffer1, sizeof(buffer1), stdin);
    yy_scan_string(buffer1);
    int i, ans = 10000000;
    for (i = 0; i < arrsize; i++) {
        yylex();
        if (arr[i] < ans) {
            ans = arr[i];
        }
    }
    printf("\n");
    printf("%d\n", ans);
    return 0;
}