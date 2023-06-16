%{
    #include <stdio.h>
    int n;
%}

%%

[0-1]+[ \n\t]  {
    printf("binary ");}

[0-7]+[ \n\t ] {printf("octal ");}

[0-9]+[ \n\t] {printf("decimal ");}

[0-9a-f]+[ \n\t] {printf("hexadecimal ");}

[^0-9a-f \n\t' ']+[ \n\t] {printf("invalid ");}



. {}

%%

int yywrap(void){
    return 1;
}

int main(){

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char input[100];
        scanf(" %[^\n ]", input);
        strcat(input, " ");
        yy_scan_string(input);
        yylex();
        yy_delete_buffer(YY_CURRENT_BUFFER);
    }

    printf("\n");

    return 0;
    
}