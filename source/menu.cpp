#include "globals.hpp"
#include "menu.hpp"
#include "algorithms.hpp"
#include "visuals.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>
#include <string>

const std::vector<std::string> MENU_TEXT = {
	"Sorting Algorithms",
	"Settings",
	"Exit"};

const std::vector<std::string> ALGO_TEXT = {
	"Back",
    "Insertion Sort",
    "Merge Sort",
    "Heap Sort",
    "Quick Sort",
	"Bubble Sort",
	"Selection Sort"};

const std::vector<std::string> SETTINGS_TEXT = {
    "Back",
	"Array Elements",
    "Delay (ms)",
    "New Array",
	"Toggle tree view",
	"Toggle new array on start"};

const std::vector<std::string> DESCRIPTION_TEXT = {
	//Write a two sentance description of Insertion Sort at an undergraduate level. Start it with "Insertion Sort works by". Do not write about best case or worst case complexity.
	" Insertion Sort works by iterating\n through an array and moving each\n element to its correct position by\n comparing it with the previous\n elements. The algorithm maintains a\n sorted subarray and inserts the next\n element in its correct position in the\n subarray.",
	" Merge Sort works by dividing the\n unsorted list into n sublists, each\n containing one element, and then\n repeatedly merging sublists to produce\n new sorted sublists until there is\n only one sublist remaining. This final\n sublist is the sorted list."
};

void Menu::clearConsole()
{
    printf("\x1b[2J");
    printf("\x1b[H");
}

Menu::Menu(const std::vector<std::string> text, void (*handlerFunction)())
{
    menuLen = text.size();
    MENU_TEXT = text;
    this->handlerFunction = handlerFunction;
}

void Menu::draw()
{
    for (int i = 0; i < menuLen; i++)
    {
        printf("\x1b[%i;%iH%s\n", i + 1, selector.length() + 1, MENU_TEXT[i].c_str());
	}
    handlerFunction();
}

void Menu::handleInput()
{
	if (kDown) 
	{
		drawMenu++;
	}

    if (kDown & KEY_DOWN)
    {
        selected++;
        if (selected > menuLen - 1)
        {
            selected = 0;
        }
    }
    else if (kDown & KEY_UP)
    {
        selected--;
        if (selected < 0)
        {
            selected = menuLen - 1;
        }
    }
}

void switchMenu(Menu *menu)
{
	drawMenu++;
	selected = 0;
	activeMenu = menu;
}

// Menu Handlers //
void settingsMenuHandler()
{
	// Handle, if user pressed A
	if (kDown & KEY_A)
	{
		switch (selected)
		{
		case 0:
			switchMenu(mainMenu);
			break;
		case 1:
			arrayLen = inputNum();
			initArray();
			break;
		case 2:
			delayMs = inputNum();
			break;
		case 3:
			initArray();
			break;
		case 4:
			isTree = !isTree;
			break;
		case 5:
			newArrayOnStart = !newArrayOnStart;
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
			switchMenu(mainMenu);
			break;
		case 1:
			if (newArrayOnStart)
			{
				initArray();
			}
			sortThread = threadCreate(insertionSort, NULL, STACKSIZE, prio - 1, 1, false);
			//have a printf here that prints on the 16th row and starts on the MENU_TEXT[1].length()/2 column, and prints MENU_TEXT[1] (which is "Insertion Sort")
			printf("\x1b[16;%iH%s\n", (20 - ALGO_TEXT[1].length()/2), ALGO_TEXT[1].c_str());
			printf("\x1b[19;1H%s\n", DESCRIPTION_TEXT[0].c_str());

			break;
		case 2:
			if (newArrayOnStart)
			{
				initArray();
			}
			sortThread = threadCreate(mergeSortInit, NULL, STACKSIZE, prio - 1, 1, false);
			printf("\x1b[16;%iH%s\n", (20 - ALGO_TEXT[2].length()/2), ALGO_TEXT[2].c_str());
			printf("\x1b[19;1H%s\n", DESCRIPTION_TEXT[1].c_str());
			break;
		case 3:
			if (newArrayOnStart)
			{
				initArray();
			}
			sortThread = threadCreate(heapSort, NULL, STACKSIZE, prio - 1, 1, false);
			break;
		case 4:
			if (newArrayOnStart)
			{
				initArray();
			}
			sortThread = threadCreate(quickSortInit, NULL, STACKSIZE, prio - 1, 1, false);
			break;
		case 5:
			if (newArrayOnStart)
			{
				initArray();
			}
			sortThread = threadCreate(bubbleSort, NULL, STACKSIZE, prio - 1, 1, false);
			break;
		case 6:
			if (newArrayOnStart)
			{
				initArray();
			}
			sortThread = threadCreate(selectionSort, NULL, STACKSIZE, prio - 1, 1, false);
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