#pragma once

#include "BaseRenderer.h"

class SoftwareRenderer : public BaseRenderer {
public:
    SoftwareRenderer(SDL_Window* window);
    ~SoftwareRenderer() override;

    void drawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) override;
    void drawFilledRect(const SDL_Rect* rect, SDL_Color color) override;
    void drawFilledCircle(int x, int y, int radius, SDL_Color color) override;
    void present() override;
};
