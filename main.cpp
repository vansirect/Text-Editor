#include <iostream>
#include<raw.h>

int main(){
   enableRaw();
   char c;

   while(read(STDIN_FILENO,&c,1)==1 && c!='q');
   
}