#pragma once
#include<unistd.h>
#include <termios.h>

struct termios orig_termios;
void disableRaw();
void enableRaw();