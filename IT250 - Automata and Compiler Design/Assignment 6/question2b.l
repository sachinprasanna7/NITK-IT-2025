%{
    #include "y.tab.h"
    extern int yylval;
%}

%%
[ \t\n]  
while return WHILE;
do return DO;
[0-9]+    return NUM;
[A-Za-z_]+    return ID;
[char|short|int|long|float|double|bool|void|wchar_t|signed|unsigned] return KEY;
"<="    return LE;
">="    return GE;
"=="    return EQ;
"!="    return NE;
"||"    return OR;
"&&"    return AND;
"<"     return LT;
">"     return GT;
[ \n]+     {}
. {return yytext[0];}
"//code" return STMT;
"$\n" return END;

%%

int yywrap()
{
    return 1;
}