#include <iostream>
#include"raw.h"
#include<stdio.h>
#include<ctype.h>
#include<unistd.h>

int main(){
   enableRaw();
   char c;

   

   while(read(STDIN_FILENO,&c,1)==1 && c!='q'){
      if(iscntrl(c)){
         printf("%d\n",c);
      }else{
      printf("%d('%c')\n",c,c);
      }
   }


}