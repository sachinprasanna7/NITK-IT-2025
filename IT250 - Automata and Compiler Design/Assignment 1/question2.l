%{
#include<stdio.h>
%}

%%

.*[0-9] {
   printf("-1\n");
   return 0;
}

[A-Z]      {printf("%c",yytext[0]+ 32);}
[a-z]      {printf("%c",yytext[0]- 32);}
[\t\n]      ECHO;
.           ECHO;
%%

int yywrap(void)
{
   return 1;
}

int main()
{
   yylex();

   return 0;
}