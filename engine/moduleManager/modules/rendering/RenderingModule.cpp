//
// Created by 11896 on 15/11/2024.
//

#include <iostream>
#include "RenderingModule.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "components/renderables/SpriteRenderable.hpp"
#include "SDL2_gfx/SDL2_rotozoom.h"

RenderingModule::RenderingModule(SDL_Renderer *renderer) : renderer(renderer) {}

void RenderingModule::Render(const std::vector<std::reference_wrapper<Renderable>>& renderables) {
    for (Renderable &renderable : renderables) {
        switch (renderable.GetRenderableType()) {
            case RECTANGLE:
                RenderRectangle(renderable);
                break;
            case ELLIPSE:
                RenderEllipse(renderable);
                break;
            case SPRITE:
                RenderSprite(renderable);
                break;
        }
    }
}



void RenderingModule::RenderRectangle(Renderable &renderable) {
    auto &rect = reinterpret_cast<RectangleRenderable &>(renderable);
    glm::ivec4 color = rect.GetColor();
    ComponentTransform &transform = *rect.componentTransform;

    // Create a surface for the rectangle
    SDL_Surface *rectSurface = SDL_CreateRGBSurfaceWithFormat(0, transform.scale.x, transform.scale.y, 32, SDL_PIXELFORMAT_RGBA32);
    if (!rectSurface) {
        std::cerr << "Failed to create rectangle surface: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FillRect(rectSurface, nullptr, SDL_MapRGBA(rectSurface->format, color.r, color.g, color.b, color.a));

    SDL_Surface *rotatedSurface = rotozoomSurface(rectSurface, transform.rotation, 1.0, SMOOTHING_ON);
    SDL_FreeSurface(rectSurface);

    if (!rotatedSurface) {
        std::cerr << "Failed to rotate rectangle surface: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, rotatedSurface);
    SDL_FreeSurface(rotatedSurface);

    if (!texture) {
        std::cerr << "Failed to create texture from rotated surface: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect destRect = {
            static_cast<int>(transform.position.x - rotatedSurface->w / 2),
            static_cast<int>(transform.position.y - rotatedSurface->h / 2),
            rotatedSurface->w,
            rotatedSurface->h
    };

    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
}


void RenderingModule::RenderEllipse(Renderable &renderable) {
    auto &ellipse = reinterpret_cast<EllipseRenderable &>(renderable);
    glm::ivec4 color = ellipse.GetColor();

    ComponentTransform &transform = *ellipse.componentTransform;

    int centerX = static_cast<int>(transform.position.x);
    int centerY = static_cast<int>(transform.position.y);
    int radiusX = static_cast<int>(transform.scale.x / 2.0f);
    int radiusY = static_cast<int>(transform.scale.y / 2.0f);

    filledEllipseRGBA(renderer, centerX, centerY, radiusX, radiusY, color.r, color.g, color.b, color.a);
}

void RenderingModule::RenderSprite(Renderable &renderable) {
    auto &sprite = reinterpret_cast<SpriteRenderable &>(renderable);
    const std::string &filePath = sprite.GetFilePath();

    int width, height;
    SDL_Texture *texture = LoadTexture(filePath, width, height);
    if (!texture) {
        return;
    }

    RenderTexture(texture, *sprite.componentTransform, width, height);

    SDL_DestroyTexture(texture);
}

SDL_Texture *RenderingModule::LoadTexture(const std::string &filePath, int &width, int &height) {
    int channels;
    unsigned char *imageData = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!imageData) {
        std::cerr << "Failed to load image: " << filePath << std::endl;
        return nullptr;
    }

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(imageData, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32);


    if (!surface) {
        std::cerr << "Failed to create SDL surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    stbi_image_free(imageData);

    if (!texture) {
        std::cerr << "Failed to create SDL texture: " << SDL_GetError() << std::endl;
    }

    return texture;
}


void RenderingModule::RenderTexture(SDL_Texture *texture, const ComponentTransform &transform, int width, int height) {
    if (!texture) {
        std::cerr << "Cannot render null texture." << std::endl;
        return;
    }

    SDL_FRect destRect = {
           (transform.position.x - transform.scale.x / 2.0f),
           (transform.position.y - transform.scale.y / 2.0f),
           transform.scale.x,
           transform.scale.y
    };

    SDL_RenderCopyExF(renderer, texture, nullptr, &destRect, transform.rotation, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}
