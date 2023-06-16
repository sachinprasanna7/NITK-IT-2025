%{
    #include "y.tab.h"
    extern int yylval;
%}

%%

[0-9.0-9]+      {                         //Numbers are valid and can be calculated
              yylval = atoi(yytext);
              return NUMBER;
            }
 
[ \t]+         ;  //Blanks are ignored

.            { return yytext[0]; }

[a-zA-Z)]+    { return 0; }

\n           { return 0; }
 
%%

int yywrap(){
    return 1;
}