#pragma once

#include <SDL.h>

class RenderingModule {
public:
    RenderingModule(SDL_Window* window);
    ~RenderingModule();
    void draw();
    void update(float delta);

private:
    SDL_Renderer* renderer;
    SDL_Texture* boxImage;
    void loadTextures();
};
