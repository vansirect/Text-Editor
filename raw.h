#pragma once
#include<unistd.h>
#include <termios.h>
#include<stdlib.h>
#include<stdio.h>

extern struct termios orig_termios;
void disableRaw();
void enableRaw();
void die (const char *s);