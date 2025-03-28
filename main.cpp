#include<iostream>
#include"input_output.h"
#include"raw.h"
#include<stdio.h>
#include<ctype.h>
#include<unistd.h>

int main(){
   enableRaw();
   char c;

   

   while(1){
      editorProcessKeypress();
   }


}