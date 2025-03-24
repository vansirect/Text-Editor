#include"raw.h"
#include <unistd.h>
#include<stdlib.h>

struct termios orig_termios;  
void disableRaw(){
    //flushes the input buffer
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig_termios);

}

void enableRaw(){
   
    //We are getting the attributes of the terminal and reading into a struct raw
    tcgetattr(STDIN_FILENO,&orig_termios);

    atexit(disableRaw);

    struct termios raw = orig_termios;
    /*
     ECHO- We are turning off echo which shows the user what they are typing on the screen
     ICANON -We are turning off canonical mode  which allows us to read input character by character instead of a full line at once
     ISIG - We are turning off SIGNT and SIGTSP to stop ctrl c and ctrl z for sending signals
     IEXTEN - Turning off ctrl v
     IXON(XON - resume transmission , X0FF - pause transmission) - We are turning off ctrl s and ctrl q 
     ICRNL(CR - carriage return , NL-  newline) - Converting \r(moves curson to the beginning of the new line) to \n(moves curson to next line but  stays in the same column)on Enter
     OPOST(O - output , POST - post processing of output)
     iflag - input flag
     lflag - local flag
     oflag - output flag
    
    
    */
    raw.c_iflag &= ~(IXON|ICRNL);
    raw.c_lflag&= ~(ECHO|ICANON|ISIG);
    raw.c_oflag &= ~(OPOST);
    //We are setting the attributes back
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);


}

