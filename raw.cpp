#include"raw.h"


struct termios orig_termios; 
void die (const char *s) {
    perror(s);
    exit(1);
}
void disableRaw(){
    //flushes the input buffer
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig_termios) == -1)die("tcsetattr");

}


void enableRaw(){
   
    //We are getting the attributes of the terminal and reading into a struct raw
    if(tcgetattr(STDIN_FILENO,&orig_termios)==-1) die("read");

    atexit(disableRaw);

    struct termios raw = orig_termios;
    /*
     ECHO       - We are turning off echo which shows the user what they are typing on the screen
     ICANON     - We are turning off canonical mode  which allows us to read input character by character instead of a full line at once
     ISIG       - We are turning off SIGNT and SIGTSP to stop ctrl c and ctrl z for sending signals
     IEXTEN     - Turning off ctrl v
     IXON(XON   - resume transmission , X0FF - pause transmission) - We are turning off ctrl s and ctrl q 
     ICRNL      - (CR- carriage return , NL-  newline) - Converting \r(moves curson to the beginning of the new line) to \n(moves curson to next line but  stays in the same column)on Enter
     \r\n       - Ensures you go to the next line and move the cursor to the beginning  of the line
     OPOST      - (O- output , POST - post processing of output)
     VMIN = 0   - returns immediately if theres no input
     VTIME = 1  - returns  when  100 milliseconds pass
     iflag      - input flag
     lflag      - local flag
     oflag      - output flag
     cc         - control characters 
     
    */
    raw.c_iflag &= ~(IXON|ICRNL);
    raw.c_lflag&= ~(ECHO|ICANON|ISIG);
    raw.c_oflag &= ~(OPOST);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] =1;
    //We are setting the attributes back
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw) == -1)die("tcsetattr");
    

}

