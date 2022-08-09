#include "globals.h"

#include <citro2d.h>

SwkbdButton button = SWKBD_BUTTON_NONE;
int selected = 0;
unsigned int arrayLen = 10;
unsigned int delayMs = 2;

s32 prio = 0;

volatile bool doneSorting = false;
volatile unsigned int activeIndex = 0;