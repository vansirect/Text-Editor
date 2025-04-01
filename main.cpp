#include<iostream>
#include"input_output.h"
#include"raw.h"
#include<stdio.h>
#include<ctype.h>
#include<unistd.h>


int main(){
   enableRaw();
   

   

   while(1){
      editorRefreshScreen();
      editorProcessKeypress();
   }


}