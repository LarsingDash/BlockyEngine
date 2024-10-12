#pragma once

#include "Renderable.h"
#include <SDL.h>

class Texture : public Renderable {
public:
    Texture(const char* filePath, IRenderer* renderer, SDL_Rect dstRect);
    ~Texture();
    void render(IRenderer* renderer) override;
    static SDL_Texture* loadTextureFromFile(const char* filePath, SDL_Renderer* renderer);
    void update(float deltaTime) override {}
private:
    SDL_Texture* texture;
    SDL_Rect dstRect;

};
