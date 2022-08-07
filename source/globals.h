#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

#define SAMPLERATE 22050
#define SAMPLESPERBUF (SAMPLERATE / 30)
#define BYTESPERSAMPLE 4

#define STACKSIZE (32 * 1024)

// Input Stuff
extern static SwkbdState swkbd;
extern static char mybuf[10];
extern SwkbdButton button;
extern u32 kDown;

extern const char *selector;

// Define Menus
extern Menu *mainMenu;
extern Menu *algoMenu;
extern Menu *settingsMenu;

extern Menu *activeMenu;

// Sound Stuff
extern ndspWaveBuf waveBuf[2];
extern u32 *audioBuffer;


// Array Stuff
extern unsigned int *array;
extern unsigned int arrayLen;
extern const unsigned int maxArrayVal;
extern unsigned int delayMs;

// Render stuff
extern C3D_RenderTarget *top;
extern u32 bar_clr;
extern u32 active_clr;
extern u32 clrClear;
extern u32 doneClr;
extern const size_t maxBars;

// Threading vars
extern Thread sortThread;
extern s32 prio;

extern volatile bool doneSorting;
extern volatile unsigned int activeIndex;

#endif