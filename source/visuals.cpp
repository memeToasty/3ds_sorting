#include "globals.h"
#include "helpers.h"
#include "visuals.h"
#include "sound.h"
#include "algorithms.h"

#include <3ds.h>
#include <citro2d.h>


void accessElement(unsigned int accessedIndex)
{
	activeIndex = accessedIndex;
	if (waveBuf[0].status == NDSP_WBUF_DONE)
	{
		fill_buffer(audioBuffer, 0, SAMPLESPERBUF * 2, 300 + (array[activeIndex] * 20));
		ndspChnWaveBufAdd(0, &waveBuf[0]);
	}
}

void finishSorting()
{
	for (unsigned short i = 0; i < arrayLen; ++i)
	{
		accessElement(i);
		ThreadSleep((unsigned int)(1000.0 / (double)arrayLen));
	}
}
// Sorting algorithms

void drawArray()
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top, clrClear);
	C2D_SceneBegin(top);

	const float width = (float)SCREEN_WIDTH / (float)arrayLen;
	for (unsigned int i = 0; i < arrayLen; i++)
	{
		const float height = (float)((float)SCREEN_HEIGHT / (float)maxArrayVal) * array[i];
		const float x = i * width;
		const float y = SCREEN_HEIGHT - height;
		if (i == activeIndex)
		{
			C2D_DrawRectSolid(x, y, 0, width, height, active_clr);
		}
		else
		{
			C2D_DrawRectSolid(x, y, 0, width, height, bar_clr);
		}
	}
}

void initArray()
{
	free(array);
	array = (unsigned int *)malloc(sizeof(unsigned int) * arrayLen);
	if (array == NULL)
	{
		exit(1);
	}
	for (unsigned int i = 0; i < arrayLen; ++i)
	{
		// array[i] = rand() % maxArrayVal;
		array[i] = (unsigned int)(((double)maxArrayVal / (double)arrayLen) * (i + 1));
	}

	for (unsigned short i = 0; i < arrayLen; ++i)
	{
		swap(rand() % arrayLen, i);
	}
}
unsigned int inputNum()
{
	swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 8);
	swkbdSetPasswordMode(&swkbd, SWKBD_PASSWORD_NONE);
	swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
	swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
	button = swkbdInputText(&swkbd, mybuf, sizeof(mybuf));
	return atoui(mybuf);
}