#pragma once

#include "SDL.h"
#include "IRenderer.h"

class BaseRenderer : public IRenderer {
protected:
    SDL_Renderer* renderer;
    SDL_Color clearColor;

public:
    BaseRenderer(SDL_Renderer* ren) : renderer(ren), clearColor({0, 0, 0, 255}) {}

    virtual void setClearColor(SDL_Color color) {
        clearColor = color;
    }

    virtual void clear() override {
        SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        SDL_RenderClear(renderer);
    }

    SDL_Renderer* getSDLRenderer() override {
        return renderer;
    }
};
