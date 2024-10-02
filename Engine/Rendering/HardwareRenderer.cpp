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

void HardwareRenderer::present() {
    SDL_RenderPresent(sdlRenderer);
}
