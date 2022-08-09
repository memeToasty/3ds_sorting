#include "globals.h"
#include "menu.h"

#include <citro2d.h>
#include <stdio.h>
#include <stdlib.h>


const char *selector = ">";
const unsigned int maxArrayVal = 100;
const size_t maxBars = 9500;

Thread sortThread;

C3D_RenderTarget *top;
u32 bar_clr;
u32 active_clr;
u32 clrClear;
u32 doneClr;

SwkbdButton button = SWKBD_BUTTON_NONE;
u32 kDown = 0;
int selected = 0;
unsigned int arrayLen = 10;
unsigned int delayMs = 2;

Menu *mainMenu;
Menu *algoMenu;
Menu *settingsMenu;

Menu *activeMenu;

ndspWaveBuf waveBuf[2];
u32 *audioBuffer;

s32 prio = 0;

volatile bool doneSorting = false;
volatile unsigned int activeIndex = 0;

unsigned int* array = (unsigned int*) malloc(1);