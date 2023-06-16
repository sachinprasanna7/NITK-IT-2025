%{
    #include <stdio.h>
%}

%%

[0-9]+[.][0-9]+ {printf("positive real");}

[-][0-9]+[.][0-9]+ {printf("negative real");}

[0-9]+ {printf("positive integer");}

[+][0-9]+ {printf("positive integer");}

[-][0-9]+ {printf("negative integer");}

[-][0-9]+[.][0-9]+[e][-][0-9]+ {printf("negative real in negative exponential form");}

[0-9]+[.][0-9]+[e][-][0-9]+ {printf("positive real in negative exponential form");}

[0-9]+[.][0-9]+[e][+][0-9]+ {printf("positive real in positive exponential form");}

[-][0-9]+[.][0-9]+[e][+][0-9]+ {printf("negative real in positive exponential form");}

[0-9]+[.][0-9]+[e][0-9]+ {printf("positive real in positive exponential form");}

[-][0-9]+[.][0-9]+[e][0-9]+ {printf("negative real in positive exponential form");}

[-][0-9]+[e][-][0-9]+ {printf("negative integer in negative exponential form");}

[0-9]+[e][-][0-9]+ {printf("positive integer in negative exponential form");}

[0-9]+[e][+][0-9]+ {printf("positive integer in positive exponential form");}

[-][0-9]+[e][+][0-9]+ {printf("negative integer in positive exponential form");}

[0-9]+[e][0-9]+ {printf("positive integer in positive exponential form");}

[-][0-9]+[e][0-9]+ {printf("negative integer in positive exponential form");}

.* {printf("neither integer nor real");}

%%

int yywrap(void){
    return 1;
}

int main(){

    yylex();

    return 0;
}