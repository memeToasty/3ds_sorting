#ifndef TEXT_H
#define TEXT_H

#include <citro2d.h>
#include <3ds.h>

class Text
{
private:
    
public:
    static C2D_TextBuf textBuf;
    C2D_Text staticText;
    static C2D_Font font;
    float xPos;
    float yPos;
    float textScale;

    Text(char* text, float x, float y, float scale);


    void render();


    static void Init();
    static void deInit();
};

#endif