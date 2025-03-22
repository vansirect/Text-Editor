#include"raw.h"
#include <unistd.h>
#include<stdlib.h>


void disableRaw(){
    tcsetattr(STDERR_FILENO,TCSAFLUSH,&orig_termios);
}

void enableRaw(){
   
    //We are getting the attributes of the terminal and reading into a struct raw
    tcgetattr(STDIN_FILENO,&orig_termios);

    atexit(disableRaw);

    struct termios raw = orig_termios;
    //We are turning off echo which shows the user what they are typing on the screen
    raw.c_cflag&= ~(ECHO);
    //We are setting the attributes back
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);


}

void disableRaw(){

}