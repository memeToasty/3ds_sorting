#ifndef NODE_H
#define NODE_H

#include "text.hpp"
#include <citro2d.h>

class Node {
    private:
        static const u32 color = C2D_Color32(0xC0, 0xC0, 0xC0, 0xFF);
        static const u32 activeColor = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
    public:
        Text* text;
        float x,y ;
        float size;

        Node(const char* text, float x, float y, float size);

        void render(bool active);
};

#endif