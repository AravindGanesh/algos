#include <stdio.h>

int main(){
  int digit;
  while((digit=fgetc(stdin))!=EOF){
    printf("%c\n", digit);
    if(digit=='\n'){
      //Your code here.
    }
    else if(digit==' '){
      //Your code here.
    }
    else{
      //Your code here.
    }
  }
  return(0);
}