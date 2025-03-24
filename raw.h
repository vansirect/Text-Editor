#pragma once
#include<unistd.h>
#include <termios.h>

extern struct termios orig_termios;
void disableRaw();
void enableRaw();