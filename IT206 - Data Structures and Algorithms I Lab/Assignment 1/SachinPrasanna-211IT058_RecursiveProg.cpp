#include <iostream>
#include <string>

using namespace std;

void recurseWords(string str,int n){
    
    if(n == 1)
    {
        str += 'b';
        words(str,n+1);
    }
    else if(n == 3)
    {
        str+='d';
        words(str,n+1);     
    }
    else if( n >= 5)
    {
        cout<<str<<'\n';   
    }
    else{
        words(str+ 'a',n+1);
        words(str+ 'c',n+1);
        words(str+ 'e',n+1);
    }

}

int main(){
    string str = "";
    recurseWords(str,0);
    return 0;
}