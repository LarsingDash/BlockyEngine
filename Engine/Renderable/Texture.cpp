#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const char* filePath, IRenderer* renderer, SDL_Rect dstRect)
        : dstRect(dstRect) {
    texture = loadTextureFromFile(filePath, renderer->getSDLRenderer());
    if (!texture) {
        std::cerr << "Failed to load texture from file: " << filePath << std::endl;
    }
}

Texture::~Texture() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Texture::render(IRenderer* renderer) {
    if (texture) {
        renderer->drawTexture(texture, nullptr, &dstRect);
    } else {
        std::cerr << "Texture is not available for rendering." << std::endl;
    }
}

SDL_Texture* Texture::loadTextureFromFile(const char* filePath, SDL_Renderer* renderer) {
    int width, height, channels;
    unsigned char* image = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
    if (!image) {
        std::cerr << "Couldn't load image: " << stbi_failure_reason() << std::endl;
        return nullptr;
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
            image, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32
    );
    if (!surface) {
        std::cerr << "Couldn't create surface: " << SDL_GetError() << std::endl;
        stbi_image_free(image);
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    stbi_image_free(image);

    return texture;
}

