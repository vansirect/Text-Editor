#include "input_output.h"
#include "raw.h"


char editorReadKey(){
    int nread;
    char c;
    /* reads the current key into c and the number of bytes into nread and if nread fails(== -1) and errno != EAGAIN means there was an error and data was available but if
    errno = EAGAIN means no data was input 
    */
    
    while((nread = read(STDIN_FILENO,&c,1))!=1){
        if(nread == -1 && errno != EAGAIN) die("read");
    }
    return c;
}
void editorProcessKeypress() {
    char c  = editorReadKey();
    switch (c)
    {
    case CTRL_KEY('q'):
       write(STDOUT_FILENO,"\x1b[2J\x1b[H",7);
       exit(0);
       break;
    }

}
// This will clear the screen as executed. "\x1b" respresents the esc key and  "[2J" tells the terminal to clear the screen and [H moves the cursor the top left corner
void editorRefreshScreen(){
    write(STDOUT_FILENO,"\x1b[2J\x1b[H",7);
    editorDrawRows();
    write(STDOUT_FILENO,"\x1b[H",3);

}
void initEditor(){
    if(getWindowSize(&E.screenrows,&E.screencols) ==-1) die("getwindowsize");
}
void editorDrawRows(){
    int y; 

    for(y = 0; y< E.screenrows; y++){
        write(STDOUT_FILENO,"~\r\n",3);
    }
}