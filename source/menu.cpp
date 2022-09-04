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
    "Insertion Sort",
    "Merge Sort",
    "Heap Sort",
    "Quick Sort",
    "Back"};

const std::vector<std::string> SETTINGS_TEXT = {
    "Array Elements",
    "Delay (ms)",
    "New Array",
	"Toggle tree view",
    "Back"};


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
			arrayLen = inputNum();
			initArray();
			break;
		case 1:
			delayMs = inputNum();
			break;
		case 2:
			initArray();
			break;
		case 3:
			isTree = !isTree;
			break;
		case 4:
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
			sortThread = threadCreate(insertionSort, NULL, STACKSIZE, prio - 1, 1, false);
			break;
		case 1:
			sortThread = threadCreate(mergeSortInit, NULL, STACKSIZE, prio - 1, 1, false);
			break;
		case 2:
			sortThread = threadCreate(heapSort, NULL, STACKSIZE, prio - 1, 1, false);
			break;
		case 3:
			sortThread = threadCreate(quickSortInit, NULL, STACKSIZE, prio - 1, 1, false);
			break;
		case 4:
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