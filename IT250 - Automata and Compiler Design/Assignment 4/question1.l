%{
#include <stdio.h>
int keywords = 0;
int numbers = 0;
int identifiers = 0;
int operators = 0;
int puncutations = 0;
int invalid = 0;
int newline = 0;
%}

%%

(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)[ \t]+ {keywords++;}

[0-9]+[ \t]+ {numbers++;}

[0-9]+[a-zA-Z_0-9]*[ \t]+ {invalid++;}

[a-zA-Z_][a-zA-Z0-9_]*[ \t]+ {identifiers++;}

[+|-|*|/|>|<|>=|<=|==|!=][ \t]+ {operators++;}

[{}().,;:%&|^!~=<>?][ \t]+ {puncutations++;}

[\n] {newline++;}

. {invalid++;}


%%
int yywrap(void){
    return 1;
}

int main() {

    FILE *filePtr = fopen("inputfile1.txt", "r");
    if (!filePtr) {
        printf("Error: Cannot open file \n");
        return -1;
    }

    yyin = filePtr;

    yylex();
    fclose(filePtr);

    printf("\nNumber of Keywords: %d", keywords);
    printf("\nNumber of Numbers: %d", numbers);
    printf("\nNumber of Identifiers: %d", identifiers);
    printf("\nNumber of Operators: %d", operators);
    printf("\nNumber of Puncutations: %d", puncutations);
    printf("\nTotal Number of Tokens are: %d\n", keywords + numbers + identifiers + operators + puncutations);

    return 0;
}