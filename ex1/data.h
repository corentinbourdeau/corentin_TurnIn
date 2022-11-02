#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <curses.h>
#include <termios.h>

typedef struct Data {
	int bytes;
	void *arr;
} Data;

extern bool runningMainThread;