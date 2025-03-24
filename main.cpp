#include <iostream>
#include"raw.h"
#include<stdio.h>
#include<ctype.h>
#include<unistd.h>

int main(){
   enableRaw();
   char c;

   

   while(1){
      char c = '\0';
      if(read(STDIN_FILENO,&c,1) ==-1) die("read");
      if(iscntrl(c)){
         printf("%d\r\n",c);
      }else{
      printf("%d('%c')\r\n",c,c);
      }

      if (c == 'q') break;
   }


}