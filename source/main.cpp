#include "globals.h"
#include "algorithms.h"
#include "menu.h"
#include "visuals.h"
#include "sound.h"
#include "text.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>
#include <vector>
#include <cstdlib>
#include <math.h>

int main(int argc, char *argv[])
{
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(maxBars);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);
	Text::Init();

	// Initialize sounds
	audioBuffer = (u32 *)linearAlloc(SAMPLESPERBUF * BYTESPERSAMPLE * 2);

	ndspInit();

	ndspSetOutputMode(NDSP_OUTPUT_STEREO);

	ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
	ndspChnSetRate(0, SAMPLERATE);
	ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);

	float mix[12];
	memset(mix, 0, sizeof(mix));
	mix[0] = 1.0;
	mix[1] = 1.0;
	ndspChnSetMix(0, mix);

	memset(waveBuf, 0, sizeof(waveBuf));
	waveBuf[0].data_vaddr = &audioBuffer[0];
	waveBuf[0].nsamples = SAMPLESPERBUF;
	waveBuf[1].data_vaddr = &audioBuffer[SAMPLESPERBUF];
	waveBuf[1].nsamples = SAMPLESPERBUF;

	ndspChnWaveBufAdd(0, &waveBuf[0]);

	// Initialize random seed
	srand(time(NULL));
	// Create screen
	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	clrClear = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	bar_clr = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
	active_clr = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	doneClr = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);

	// Initialize Menus
	mainMenu = new Menu(MENU_TEXT, &mainMenuHandler);
	settingsMenu = new Menu(SETTINGS_TEXT, &settingsMenuHandler);
	algoMenu = new Menu(ALGO_TEXT, &algoMenuHandler);

	activeMenu = mainMenu;

	Text *test = new Text("Test");

	initArray();

	// Initialize Threads
	svcGetThreadPriority(&prio, CUR_THREAD_HANDLE);
	APT_SetAppCpuTimeLimit(30);

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		kDown = hidKeysDown();
		gspWaitForVBlank();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);
		
		
		activeMenu->handleInput();
		if (drawMenu > 0)
		{
			Menu::clearConsole();
			printf("\x1b[%i;1H%s", selected + 1, selector);
			activeMenu->draw();
			drawMenu--;
		}
		//test->render(10.0f,10.0f,0.5f);
		

		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		drawArray();

		C3D_FrameEnd(0);
		gfxFlushBuffers();
		// gfxSwapBuffers();

		if (doneSorting)
		{
			threadJoin(sortThread, 10000000LL);
			threadFree(sortThread);
			activeIndex = UINT32_MAX;
			doneSorting = false;
		}
	}


	Text::deInit();
	ndspExit();
	linearFree(audioBuffer);

	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
