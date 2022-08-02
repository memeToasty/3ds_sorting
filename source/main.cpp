#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>
#include "menu.h"
#include <vector>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

// TODO:
// Refactor Menu Button handling


// Input Stuff
static SwkbdState swkbd;
static char mybuf[10];
SwkbdButton button = SWKBD_BUTTON_NONE;
u32 kDown;


const char *selector = "> ";


// Define Menus
Menu *mainMenu;
Menu *algoMenu;
Menu *settingsMenu;

Menu *activeMenu;
// Main menu text
const std::vector<std::string> MENU_TEXT = {
	"Sorting Algorithms",
	"Settings",
	"Exit"};

// Algo menu text
const std::vector<std::string> ALGO_TEXT = {
	"Insertion Sort",
	"Merge Sort",
	"Heap Sort",
	"Back"};

// Settings text
const std::vector<std::string> SETTINGS_TEXT = {
	"Array Elements",
	"Delay (ms)",
	"Back"};

int selected = 0;

bool arrayUpdate = false;

unsigned int* array;
unsigned int arrayLen = 10;
const unsigned int maxArrayVal = 100;
unsigned int delayMs = 2;

C3D_RenderTarget* top;
u32 bar_clr;
u32 active_clr;
const size_t maxBars = 9500;

// Threading vars
Thread sortThread;
s32 prio = 0;
#define STACKSIZE (4 * 1024)

volatile bool doneSorting = false;
volatile unsigned int activeIndex = 0;

int atoui(const char* str){
    unsigned int num = 0;
    int i = 0;
    while (str[i] && (str[i] >= '0' && str[i] <= '9')){
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return num;
}


void switchMenu(Menu* menu)
{
	activeMenu = menu;
}
void ThreadSleep(unsigned int ms) {
	svcSleepThread(1000000ULL * (u32) ms);
}
// Sorting algorithms
void swap(unsigned short index1, unsigned short index2) {
	unsigned int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;

}
void insertionSort(void* args) {
	for (unsigned int i = 1; i < arrayLen; i++) {
		unsigned short j = i;
		while (j > 0 && array[j] < array[j-1]) {
			swap(j,j-1);
			j--;
			activeIndex = j;
			ThreadSleep(delayMs);
		}
	}
	doneSorting = true;
}

void drawArray() {
	const float width = (float)SCREEN_WIDTH / arrayLen;
	for (unsigned int i = 0; i < arrayLen; i++) {
		const float height = (float)(SCREEN_HEIGHT / maxArrayVal) * array[i];
		const float x = i * width;
		const float y = SCREEN_HEIGHT - height;
		if (i == activeIndex) {
			C2D_DrawRectSolid(x, y, 0, width, height, active_clr);	
		} else {
			C2D_DrawRectSolid(x, y, 0, width, height, bar_clr);
		}
		
	}
}

void initArray() {
	free(array);
	array = (unsigned int*)malloc(sizeof(unsigned int) * arrayLen);
	if (array == NULL) {
		exit(1);
	}
	for (unsigned int i = 0; i < arrayLen; i++) {
		array[i] = rand() % maxArrayVal;
	}
	arrayUpdate = true;
}
unsigned int inputNum() {
	swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 8);
	swkbdSetPasswordMode(&swkbd, SWKBD_PASSWORD_NONE);
	swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK , 0, 0);
	swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
	button = swkbdInputText(&swkbd, mybuf, sizeof(mybuf));
	return atoui(mybuf);
}

void settingsMenuHandler()
{	
	// Handle, if user pressed A
	if (kDown & KEY_A)
	{
		switch (selected)
		{
		case 0:
			arrayLen = inputNum();
			initArray();
			if (array == NULL) 
			{
				switchMenu(mainMenu);
			}
			break;
		case 1:
			delayMs = inputNum();
			break;
		case 2:
			switchMenu(mainMenu);
			break;

		default:
			break;
		}
	}

	// Handle, if user pressed B
	if (kDown & KEY_B)
	{
		switchMenu(mainMenu);
	}
}
void algoMenuHandler()
{
	// Handle, if user pressed A
	if (kDown & KEY_A)
	{
		switch (selected)
		{
		case 0:
			sortThread = threadCreate(insertionSort, NULL, STACKSIZE, prio-1, 1, false);
			break;
		case 3:
			switchMenu(mainMenu);
			break;

		default:
			break;
		}
	}

	// Handle, if user pressed B
	if (kDown & KEY_B)
	{
		switchMenu(mainMenu);
	}
}

void mainMenuHandler()
{
	// Handle if user presses A
	if (kDown & KEY_A)
	{
		switch (selected)
		{
		case 0:
			switchMenu(algoMenu);
			break;
		case 1:
			switchMenu(settingsMenu);
			break;
		case 2:
			exit(0);
			break;
		default:
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(maxBars);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screen
	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	u32 clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);
	bar_clr = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
	active_clr = C2D_Color32(0xFF, 0x00, 0x00, 0xFD);


	// Initialize Menus
	
	mainMenu = new Menu(MENU_TEXT, &kDown, &selected, &mainMenuHandler);
	settingsMenu = new Menu(SETTINGS_TEXT, &kDown, &selected, &settingsMenuHandler);
	algoMenu = new Menu(ALGO_TEXT, &kDown, &selected, &algoMenuHandler);

	Menu *menus[] = {
		mainMenu,
		settingsMenu,
		algoMenu
	};
	activeMenu = mainMenu;

	initArray();

	//Initialize Threads
	svcGetThreadPriority(&prio, CUR_THREAD_HANDLE);
	// Main loop

	APT_SetAppCpuTimeLimit(30);
	while (aptMainLoop())
	{	
		hidScanInput();

		kDown = hidKeysDown();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);
		
		gspWaitForVBlank();
		Menu::clearConsole();
		
		printf("\x1b[%i;1H%s", selected + 1, selector);
		activeMenu->draw();

		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		drawArray();

		C3D_FrameEnd(0);
		gfxFlushBuffers();
		//gfxSwapBuffers();


		if (doneSorting) {
			threadJoin(sortThread, 10000000LL);
			threadFree(sortThread);
			doneSorting = false;
		}
	}

	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
