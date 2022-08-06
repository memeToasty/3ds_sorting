#ifndef MAIN_H
#define MAIN_H

#include <3ds.h>
#include <citro2d.h>
#include "menu.h"


#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

#define SAMPLERATE 22050
#define SAMPLESPERBUF (SAMPLERATE / 30)
#define BYTESPERSAMPLE 4

#define STACKSIZE (32 * 1024)

// Input Stuff
static SwkbdState swkbd;
static char mybuf[10];
SwkbdButton button;
u32 kDown;

const char *selector;

// Define Menus
Menu *mainMenu;
Menu *algoMenu;
Menu *settingsMenu;

Menu *activeMenu;

// Sound Stuff
ndspWaveBuf waveBuf[2];
u32 *audioBuffer;


// Array Stuff
unsigned int *array;
unsigned int arrayLen;
extern const unsigned int maxArrayVal = 100;
unsigned int delayMs;

// Render stuff
C3D_RenderTarget *top;
u32 bar_clr;
u32 active_clr;
u32 clrClear;
u32 doneClr;
extern const size_t maxBars = 9500;

// Threading vars
Thread sortThread;
s32 prio = 0;

volatile bool doneSorting;
volatile unsigned int activeIndex;

void fill_buffer(void *audioBuffer, size_t offset, size_t size, int frequency);
int atoui(const char *str);
void accessElement(unsigned int accessedIndex);
void ThreadSleep(unsigned int ms);
void finishSorting();
void drawArray();
void initArray();
unsigned int inputNum();

void settingsMenuHandler();
void algoMenuHandler();
void mainMenuHandler();

int main(int argc, char *argv[]);

#endif