#pragma once

#include "SDL.h"
#include "../Renderable.h"

class Rectangle : public Renderable {
public:
    SDL_Rect rect;
    SDL_Color color;

    Rectangle(int x, int y, int w, int h, SDL_Color col);

    void render(IRenderer* renderer) override;
};
