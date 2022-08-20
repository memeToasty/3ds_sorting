#include "text.h"
#include <citro2d.h>

C2D_TextBuf Text::textBuf;
C2D_Font Text::font;

void Text::Init()
{
    cfguInit();
    Text::textBuf = C2D_TextBufNew(4096);
    Text::font = C2D_FontLoadSystem(CFG_REGION_EUR);
}

void Text::deInit()
{
    C2D_TextBufDelete(textBuf);
    C2D_FontFree(font);
    cfguExit();
}

Text::Text(char *text, float x, float y, float scale)
{
    if (font == NULL)
    {
        this->~Text();
    }
    this->xPos = x;
    this->yPos = y;
    this->textScale = scale;
    C2D_TextFontParse(&staticText, font, textBuf, text);
    C2D_TextOptimize(&staticText);
}

void Text::render()
{
    C2D_DrawText(&staticText, 0, xPos, yPos, 0.0f, textScale, textScale);
}
