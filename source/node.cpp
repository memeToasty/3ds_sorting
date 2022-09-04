#include "globals.hpp"
#include "node.hpp"
#include <citro2d.h>

Node::Node(const char* text, float x, float y, float size) {
    this->size = size * 20;
    this->x = x;
    this->y = y;
    //TODO Fix text positioning on Circle
    this->text = new Text(text, &this->x, &this->y, size);
    *this->text->xPos -= this->text->staticText.width / 2;
}

void Node::render(bool active) {


    if (active) {
        C2D_DrawCircleSolid(x, y, 0, size, activeColor);
    } else {
        C2D_DrawCircleSolid(x, y, 0, size, color);
    }
    this->text->render();
}