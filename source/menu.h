#include <string>
#include <vector>

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