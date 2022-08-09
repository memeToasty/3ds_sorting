#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>

// Main menu text
extern const std::vector<std::string> MENU_TEXT;

// Algo menu text
extern const std::vector<std::string> ALGO_TEXT;

// Settings text
extern const std::vector<std::string> SETTINGS_TEXT;


class Menu
{
    private:
        u32* kDown;
        int* selected;
        const std::string selector = ">";
        
    public:
        static void clearConsole();
        int menuLen;
        Menu(const std::vector<std::string> text, u32* kDown, int *selected, void (*handlerFunction)());
        
        void draw();
        void handleInput();
        std::vector<std::string> MENU_TEXT;
        void (*handlerFunction)();
};

void switchMenu(Menu *menu);

void settingsMenuHandler();
void algoMenuHandler();
void mainMenuHandler();

#endif