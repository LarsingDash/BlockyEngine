#include "Circle.h"

Circle::Circle(int centerX, int centerY, int r, SDL_Color col) {
    x = centerX;
    y = centerY;
    radius = r;
    color = col;
}

void Circle::render(IRenderer* renderer) {
    renderer->drawFilledCircle(x, y, radius, color);
}
