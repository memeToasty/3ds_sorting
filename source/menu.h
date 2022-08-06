#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

// Main menu text
extern const std::vector<std::string> MENU_TEXT  = {
	"Sorting Algorithms",
	"Settings",
	"Exit"};

// Algo menu text
extern const std::vector<std::string> ALGO_TEXT = {
    "Insertion Sort",
    "Merge Sort",
    "Heap Sort",
    "Quick Sort",
    "Back"};

// Settings text
extern const std::vector<std::string> SETTINGS_TEXT = {
    "Array Elements",
    "Delay (ms)",
    "New Array",
    "Back"};


// Selected menu item
int selected;

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

#endif