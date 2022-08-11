#ifndef TEXT_H
#define TEXT_H

#include <citro2d.h>
#include <3ds.h>

class Text
{
private:
    static C2D_TextBuf textBuf;
    C2D_Text staticText;
    static C2D_Font font;
    
public:
    Text(char* text);
    ~Text();


    void render(float x, float y, float scale);


    static void Init();
    static void deInit();
};

#endif