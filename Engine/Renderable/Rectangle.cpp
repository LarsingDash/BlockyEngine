#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int w, int h, SDL_Color col) {
    rect = { x, y, w, h };
    color = col;
}

void Rectangle::render(IRenderer* renderer) {
    renderer->drawFilledRect(&rect, color);
}
