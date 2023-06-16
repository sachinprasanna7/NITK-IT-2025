%{
    #include "y.tab.h"
    extern int yylval;
%}

%%

[\t \n] {}    
if return IF;
else return ELSE;
[0-9]+    return NUM;
[A-Za-z_]+ return ID;
[char|short|int|long|float|double|bool|void|wchar_t|signed|unsigned] return KEY;
"<="         return LE;
">="         return GE;
"=="         return EQ;
"!="          return NE;
"||"            return OR;
"&&"         return AND;
">"           return GT;
"<"           return LT;
"//code"          return STMT;
.                return yytext[0];
"$\n"           return END;

%%

int yywrap(){
    return 1;
}