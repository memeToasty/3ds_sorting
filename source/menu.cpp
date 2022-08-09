#include "globals.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>
#include <string>

void Menu::clearConsole()
{
    printf("\x1b[2J");
    printf("\x1b[H");
}

Menu::Menu(const std::vector<std::string> text, u32 *kDown, int *selected, void (*handlerFunction)())
{
    menuLen = text.size();
    MENU_TEXT = text;
    this->kDown = kDown;
    this->selected = selected;
    this->handlerFunction = handlerFunction;
}

void Menu::draw()
{
    handleInput();
    for (int i = 0; i < menuLen; i++)
    {
        printf("\x1b[%i;%iH%s\n", i + 1, selector.length() + 1, MENU_TEXT[i].c_str());
    }
    handlerFunction();
}

void Menu::handleInput()
{
    if (*kDown & KEY_DOWN)
    {
        *selected = *selected + 1;
        if (*selected > menuLen - 1)
        {
            *selected = 0;
        }
    }
    else if (*kDown & KEY_UP)
    {
        *selected = *selected - 1;
        if (*selected < 0)
        {
            *selected = menuLen - 1;
        }
    }
}

void switchMenu(Menu *menu)
{
	selected = 0;
	activeMenu = menu;
}