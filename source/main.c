#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

// TODO:
// Refactor Menu Button handling


// Input Stuff
static SwkbdState swkbd;
static char mybuf[10];
SwkbdButton button = SWKBD_BUTTON_NONE;
u32 kDown;

const char *ALGORITHMS[] = {"INSERTION-SORT", "MERGE-SORT", "HEAP-SORT"};

const char *selector = "> ";

// Main menu text
const char *MENU_TEXT[] = {
	"Sorting Algorithms",
	"Settings",
	"Exit"};
const int16_t menuLen = sizeof(MENU_TEXT) / sizeof(MENU_TEXT[0]);

// Algo menu text
const char *ALGO_TEXT[] = {
	"Insertion Sort",
	"Merge Sort",
	"Heap Sort",
	"Back"};
const int16_t algoMenuLen = sizeof(ALGO_TEXT) / sizeof(ALGO_TEXT[0]);

// Settings text
const char *SETTINGS_TEXT[] = {
	"Array Elements",
	"Back"};
const int16_t settingsMenuLen = sizeof(SETTINGS_TEXT) / sizeof(SETTINGS_TEXT[0]);

int selected = 0;

bool arrayUpdate = false;

unsigned int* array;
unsigned int arrayLen = 10;
const unsigned int maxArrayVal = 100;

C3D_RenderTarget* top;
u32 bar_clr;
const size_t maxBars = 9500;

// current context Menu the user is in
// 0 = main menu
// 1 = sorting algorithms menu
// 2 = Array settings menu
unsigned int currentMenu = 0;

int atoui(const char* str){
    unsigned int num = 0;
    int i = 0;
    while (str[i] && (str[i] >= '0' && str[i] <= '9')){
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return num;
}

void clearConsole()
{
	printf("\x1b[2J");
}

void switchMenu(int menu)
{
	selected = 0;
	currentMenu = menu;
}

void drawArray() {
	const float width = (float)SCREEN_WIDTH / arrayLen;
	for (unsigned int i = 0; i < arrayLen; i++) {
		const float height = (float)(SCREEN_HEIGHT / maxArrayVal) * array[i];
		const float x = i * width;
		const float y = SCREEN_HEIGHT - height;
		C2D_DrawRectSolid(x, y, 0, width, height, bar_clr);
	}
}

void initArray() {
	free(array);
	array = (unsigned int*)malloc(sizeof(unsigned int) * arrayLen);
	if (array == NULL) {
		exit(1);
	}
	for (int i = 0; i < arrayLen; i++) {
		array[i] = rand() % maxArrayVal;
	}
	arrayUpdate = true;
}

void handleArraySize() {
	swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 8);
	swkbdSetPasswordMode(&swkbd, SWKBD_PASSWORD_NONE);
	swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK , 0, 0);
	swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
	button = swkbdInputText(&swkbd, mybuf, sizeof(mybuf));
	arrayLen = atoui(mybuf);
}

void settingsMenu()
{	
	clearConsole();
	// Handle input
	if (kDown & KEY_DOWN)
	{
		selected++;
		if (selected > settingsMenuLen - 1)
		{
			selected = 0;
		}
	}
	else if (kDown & KEY_UP)
	{
		selected--;
		if (selected < 0)
		{
			selected = settingsMenuLen - 1;
		}
	}
	// Print menu
	printf("\x1b[%i;1H%s", selected + 1, selector);
	for (unsigned int i = 0; i < settingsMenuLen; i++)
	{
		printf("\x1b[%i;%iH%s\n", i + 1, strlen(selector), SETTINGS_TEXT[i]);
	}

	// Handle, if user pressed A
	if (kDown & KEY_A)
	{
		switch (selected)
		{
		case 0:
			handleArraySize();
			initArray();
			if (array == NULL) 
			{
				switchMenu(0);
			}
			break;
		case 1:
			switchMenu(0);
			break;

		default:
			break;
		}
	}

	// Handle, if user pressed B
	if (kDown & KEY_B)
	{
		switchMenu(0);
	}
}
void algoMenu()
{
	clearConsole();
	// Handle input
	if (kDown & KEY_DOWN)
	{
		selected++;
		if (selected > algoMenuLen - 1)
		{
			selected = 0;
		}
	}
	else if (kDown & KEY_UP)
	{
		selected--;
		if (selected < 0)
		{
			selected = algoMenuLen - 1;
		}
	}

	// Print menu
	printf("\x1b[%i;1H%s", selected + 1, selector);
	for (unsigned int i = 0; i < algoMenuLen; i++)
	{
		printf("\x1b[%i;%iH%s\n", i + 1, strlen(selector), ALGO_TEXT[i]);
	}
	// Handle, if user pressed A
	if (kDown & KEY_A)
	{
		switch (selected)
		{
		case 3:
			switchMenu(0);
			break;

		default:
			break;
		}
	}

	// Handle, if user pressed B
	if (kDown & KEY_B)
	{
		switchMenu(0);
	}
}

void menu()
{
	clearConsole();

	// Handle input
	if (kDown & KEY_DOWN)
	{
		selected++;
		if (selected > menuLen - 1)
			selected = 0;
	}
	else if (kDown & KEY_UP)
	{
		selected--;
		if (selected < 0)
			selected = menuLen - 1;
	}

	// Print menu
	printf("\x1b[%i;1H%s", selected + 1, selector);
	for (unsigned int i = 0; i < menuLen; i++)
	{
		printf("\x1b[%i;%iH%s\n", i + 1, strlen(selector), MENU_TEXT[i]);
	}

	// Handle if user presses A
	if (kDown & KEY_A)
	{
		switch (selected)
		{
		case 0:
			switchMenu(1);
			break;
		case 1:
			switchMenu(2);
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


	initArray();
	// Main loop
	while (aptMainLoop())
	{
		//gspWaitForVBlank();
		//gfxSwapBuffers();
		hidScanInput();

		kDown = hidKeysDown();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);


		switch (currentMenu)
		{
		case 0:
			menu();
			break;
		case 1:
			algoMenu();
			break;
		case 2:
			settingsMenu();
			break;
		}

		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		drawArray();

		C3D_FrameEnd(0);
	}

	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
