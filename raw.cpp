#include"raw.h"
#include "input_output.h"

void die (const char *s) {
    write(STDOUT_FILENO,"\x1b[2J\x1b[H",7);
    perror(s);
    exit(1);
}
void disableRaw(){
    //flushes the input buffer
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&E.orig_termios) == -1)die("tcsetattr");

}

int getCursorPosition(int *rows, int *cols){

    char buf[32];
    unsigned int i = 0;

    if (write(STDOUT_FILENO,"\x1b[6n",4)!=4)return -1;
    
    while(i<sizeof(buf)-1){
        if(read(STDIN_FILENO,&buf[i],1)!=1) break;
        if(buf[i]=='R')break;
        i++;
    }
    
    buf[i]= '\0';

    printf("\r\n&buf[1]: '%s' \r\n",&buf[1]);
    editorReadKey();
    return -1;
}
int getWindowSize(int * rows , int * cols){
    struct winsize ws;
    // this is the fall back if getting the information from the terminal (ws) reads -1  we use the cursor position estimate else we use the normal method
    if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws) ==-1||ws.ws_col ==0){
        // basically what we are doing is \x1b[999C moves the cursor far right and \x1b[999B moves it down 999 columns and rows and records the position 
        if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B",12)!=12) return -1;
        return getCursorPosition(rows,cols);
    }else{
        *cols = ws.ws_col;
        *rows = ws.ws_row;

        return 0;
    }
}


void enableRaw(){
   
    //We are getting the attributes of the terminal and reading into a struct raw
    if(tcgetattr(STDIN_FILENO,&E.orig_termios)==-1) die("read");

    atexit(disableRaw);

    struct termios raw = E.orig_termios;
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

