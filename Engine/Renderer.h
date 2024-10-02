#pragma once

#include <SDL.h>

class Renderer {
public:
    virtual ~Renderer() {}
    virtual void clear() = 0;
    virtual void drawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) = 0;
    virtual void present() = 0;
};
