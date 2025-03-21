#include<raw.h>

void enableRaw(){
    struct termios raw;
    //We are getting the attributes of the terminal and reading into a struct raw
    tcgetattr(STDIN_FILENO,&raw);
    //We are 
    raw.c_cflag&= ~(ECHO);
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);

}