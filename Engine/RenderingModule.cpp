#define STB_IMAGE_IMPLEMENTATION

#include "RenderingModule.h"
#include "stb_image.h"
#include <SDL.h>
#include <iostream>

RenderingModule::RenderingModule(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
    }
    loadTextures();
}

RenderingModule::~RenderingModule() {
    SDL_DestroyTexture(boxImage);
    SDL_DestroyRenderer(renderer);
}

void RenderingModule::loadTextures() {
    int width, height, channels;
    unsigned char* image = stbi_load("../assets/ghost.png", &width, &height, &channels, STBI_rgb_alpha);
    if (!image) {
        std::cerr << "Couldn't load image" << std::endl;
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(image, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32);
    boxImage = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void RenderingModule::draw() {
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    //pacman ghost png als test
    SDL_FRect rect{360, 260, 80, 80};
    SDL_RenderCopyExF(renderer, boxImage, nullptr, &rect, 0, nullptr, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}

void RenderingModule::update(float delta) {

}
