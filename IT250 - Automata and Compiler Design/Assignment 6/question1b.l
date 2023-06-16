%{
    #include "y.tab.h"
    extern int yylval;
%}

%%
[\t \n]  
switch    return SWITCH;
case return CASE;
break return BREAK;
default return DEFAULT;

[0-9]+    return NUM;
[A-Za-z_]+ return ID;
"<="    return LE;
">="    return GE;
"=="    return EQ;
"!="    return NE;
"||"    return OR;
"&&"    return AND;
">"           return GT;
"<"           return LT;

. {return yytext[0];}
"//code" return STMT;
"$\n" return END;

%%


int yywrap()
{
    return 0;
}