#pragma once

#include "SDL.h"

class IRenderer {

public:
    virtual ~IRenderer() {}
    virtual void clear() = 0;
    virtual void drawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) = 0;
    virtual void drawFilledRect(const SDL_Rect* rect, SDL_Color color) = 0;
    virtual void drawFilledCircle(int x, int y, int radius, SDL_Color color) = 0;
    virtual void setClearColor(SDL_Color color) = 0;
    virtual void present() = 0;
};
