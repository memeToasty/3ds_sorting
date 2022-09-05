#include "globals.hpp"
#include "node.hpp"
#include <citro2d.h>

Node::Node(const char* text, float x, float y, float scale) {
    this->scale = scale;
    this->x = x;
    this->y = y;

    this->text = new Text(text, x, y, scale);
}

void Node::render(bool active) {

    this->text->xPos = this->x - (this->text->staticText.width / 2 * scale);
    this->text->yPos = this->y - (this->scale * 15);

    if (active) {
        C2D_DrawCircleSolid(x, y, 0, scale * 15, activeColor);
    } else {
        C2D_DrawCircleSolid(x, y, 0, scale * 15, color);
    }
    this->text->render();
}