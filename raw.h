#pragma once
#include<unistd.h>
#include <termios.h>
#include<stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include <errno.h>
#include <cerrno>
#include<sys/ioctl.h>
#define CTRL_KEY(key) ((key)& 0x1f)

struct editorConfig{
    int screenrows;
    int screencols;
    struct termios orig_termios; 
};

struct editorConfig E;

void disableRaw();
void enableRaw();
void editorProcessKeypress();
void die (const char *s);
int getWindowSize(int * rows , int * cols);
 