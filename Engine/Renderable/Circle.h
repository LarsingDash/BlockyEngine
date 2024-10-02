#pragma once

#include <SDL.h>
#include "Renderable.h"

class Circle : public Renderable {
public:
    int x, y;
    int radius;
    SDL_Color color;
    Circle(int centerX, int centerY, int r, SDL_Color col);

    void render(IRenderer* renderer) override;
};
