#include "SoftwareRenderer.h"

SoftwareRenderer::SoftwareRenderer(SDL_Window* window) {
    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
}

SoftwareRenderer::~SoftwareRenderer() {
    SDL_DestroyRenderer(sdlRenderer);
}

void SoftwareRenderer::clear() {
    SDL_RenderClear(sdlRenderer);
}

void SoftwareRenderer::drawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) {
    SDL_RenderCopy(sdlRenderer, texture, srcRect, dstRect);
}

void SoftwareRenderer::present() {
    SDL_RenderPresent(sdlRenderer);
}
