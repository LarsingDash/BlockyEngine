#include "HardwareRenderer.h"

HardwareRenderer::HardwareRenderer(SDL_Window* window) {
    // IRenderer maar dan GPU based (hardware accelerated)
    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

HardwareRenderer::~HardwareRenderer() {
    SDL_DestroyRenderer(sdlRenderer);
}

void HardwareRenderer::clear() {
    SDL_RenderClear(sdlRenderer);
}

void HardwareRenderer::drawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) {
    SDL_RenderCopy(sdlRenderer, texture, srcRect, dstRect);
}

void HardwareRenderer::drawFilledRect(const SDL_Rect* rect, SDL_Color color) {
    SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(sdlRenderer, rect);
}

void HardwareRenderer::drawFilledCircle(int x, int y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);

    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(sdlRenderer, x + dx, y + dy);
            }
        }
    }
}

void HardwareRenderer::present() {
    SDL_RenderPresent(sdlRenderer);
}
