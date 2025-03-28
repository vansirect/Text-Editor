#pragma once
#include<unistd.h>
#include <termios.h>
#include<stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include <errno.h>
#include <cerrno>
#define CTRL_KEY(key) ((key)& 0x1f)

extern struct termios orig_termios;
void disableRaw();
void enableRaw();
void editorProcessKeypress();
void die (const char *s);
