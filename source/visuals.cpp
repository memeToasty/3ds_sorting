#include "globals.hpp"
#include "helpers.hpp"
#include "visuals.hpp"
#include "sound.hpp"
#include "algorithms.hpp"
#include "text.hpp"

#include <3ds.h>
#include <citro2d.h>
#include <math.h>

SwkbdState swkbd;
char mybuf[10];

static const int PADDING = 30;

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
	C2D_SceneBegin(top);
	C2D_TargetClear(top, clrClear);

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

void drawTree() 
{
	//TODO: Arrange items in Binary Tree form
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_SceneBegin(top);
	C2D_TargetClear(top, clrClear);
	
	for (unsigned short i = 0; i < nodeArray.size(); i++)
	{
		Node* node = nodeArray.at(i);
		node->text->text = std::to_string(array[i]).c_str();
		
		node->render(activeIndex == i);
	}
	
	
	C2D_TextBufClear(Text::textBuf);
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
	// Init Tree view
	nodeArray.clear();

	unsigned short height = (unsigned short) floor(log2(arrayLen));
	float yGap = (SCREEN_HEIGHT  - (2 * PADDING)) / height;
	//Go through every layer of binary tree with size of the nodeArray
	for (unsigned short h = 0; h <= height; ++h) {
		
		float leftOffset = SCREEN_WIDTH * (1.0f / (pow(2, h+1)));
		float xGap = (SCREEN_WIDTH) / pow(2,h);
		// Go through every object on that layer
		for (unsigned short i = 0; i < (unsigned short) pow(2,h); ++i) {
			int absoluteI = pow(2,h) - 1 + i;

			if (absoluteI > (int) arrayLen - 1) {
				break;
			}
			
			nodeArray.push_back(new Node(std::to_string(array[i]).c_str(), leftOffset + i * xGap, h * yGap + PADDING, 10.0f / arrayLen ));
		}
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