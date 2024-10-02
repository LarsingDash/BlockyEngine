#pragma once

#include "IRenderer.h"

class SoftwareRenderer : public IRenderer {
public:
    SoftwareRenderer(SDL_Window* window);
    ~SoftwareRenderer() override;

    void clear() override;
    void drawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) override;
    void drawFilledRect(const SDL_Rect* rect, SDL_Color color) override;
    void drawFilledCircle(int x, int y, int radius, SDL_Color color) override;

    void present() override;

private:
    SDL_Renderer* sdlRenderer;
};
