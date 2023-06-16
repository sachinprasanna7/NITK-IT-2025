%{
 #include<stdio.h>
 #include<string.h>
 #include <stdbool.h>
 bool flag = false;
 int i=0; 
 int input_array[2];
%}

%%
[0-9]+ {input_array[i]=atoi(yytext);
        i++;
        
        if (i>=2){
        if(!flag){
        if (input_array[0]>input_array[1]){
            printf("%d\n", input_array[1]);
            printf("Thank you\n");
        }
        else{
            printf("%d\n", input_array[1]);
            printf("Sorry\n");
        }
        }
        else {
          input_array[1] = atoi(yytext);
          return 0;
        }
        i=0;
        fflush(stdin);
        return 0;       
        }       
    }

[\n\t ' '] {};
.* {
    flag = true;   
    i++; 
    if(i==2){ 
        printf("%s\nInvalid\n", yytext);
        exit(0);
      }  
}
      
%%
 
int main(){  
    yylex();
    if(flag) printf("%d\nInvalid\n",input_array[1]);
    return 0;
}

int yywrap(void){
   return 1;
}