#pragma once

#include "IRenderer.h"

class HardwareRenderer : public IRenderer {
public:
    HardwareRenderer(SDL_Window* window);
    ~HardwareRenderer() override;

    void clear() override;
    void drawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) override;
    void drawFilledRect(const SDL_Rect* rect, SDL_Color color) override;
    void drawFilledCircle(int x, int y, int radius, SDL_Color color) override;
    void present() override;

private:
    SDL_Renderer* sdlRenderer;
};
