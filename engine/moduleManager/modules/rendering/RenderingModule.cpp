//
// Created by 11896 on 15/11/2024.
//

#include "RenderingModule.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"


RenderingModule::RenderingModule(SDL_Renderer *renderer) : renderer(renderer) {}

RenderingModule::~RenderingModule() = default;

void RenderingModule::Render(const std::vector<std::reference_wrapper<Renderable>> &renderables) {
    for (Renderable &renderable: renderables) {
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

    SDL_Surface *rectSurface = SDL_CreateRGBSurfaceWithFormat(0, static_cast<int>(transform.scale.x),
                                                              static_cast<int>(transform.scale.y), 32,
                                                              SDL_PIXELFORMAT_RGBA32);
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
            static_cast<int>(transform.position.x - (float) rotatedSurface->w / 2),
            static_cast<int>(transform.position.y - (float) rotatedSurface->h / 2),
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

    auto centerX = static_cast<Sint16>(transform.position.x);
    auto centerY = static_cast<Sint16>(transform.position.y);
    auto radiusX = static_cast<Sint16>(transform.scale.x / 2.0f);
    auto radiusY = static_cast<Sint16>(transform.scale.y / 2.0f);

    filledEllipseRGBA(renderer, centerX, centerY, radiusX, radiusY, color.r, color.g, color.b, color.a);
}

void RenderingModule::RenderSprite(Renderable &renderable) {
    auto &sprite = reinterpret_cast<SpriteRenderable &>(renderable);

    int width, height;
    SDL_Texture *texture = LoadTexture(sprite, width, height);
    if (!texture) {
        return;
    }

    RenderTexture(texture, *sprite.componentTransform);
}

SDL_Texture* RenderingModule::LoadTexture(const SpriteRenderable &sprite, int &width, int &height) {
    const std::string &spriteTag = sprite.GetSpriteTag();

    // Check if the texture is already cached
    auto it = textureCache.find(spriteTag);
    if (it != textureCache.end()) {
        SDL_QueryTexture(it->second.get(), nullptr, nullptr, &width, &height);
        return it->second.get();
    }

    //Load image using stb_image
    const std::string &filePath = sprite.GetFilePath();
    int channels;
    unsigned char *imageData = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (!imageData) {
        std::cerr << "Failed to load image: " << filePath << std::endl;
        return nullptr;
    }

    // Create an SDL surface
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(imageData, width, height, 32, width * 4,
                                                              SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        std::cerr << "Failed to create SDL surface: " << SDL_GetError() << std::endl;
        stbi_image_free(imageData);
        return nullptr;
    }

    std::shared_ptr<SDL_Texture> texture(SDL_CreateTextureFromSurface(renderer, surface),
                                         [](SDL_Texture *t) { SDL_DestroyTexture(t); });
    SDL_FreeSurface(surface);
    stbi_image_free(imageData);

    if (!texture) {
        std::cerr << "Failed to create SDL texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    textureCache.emplace(spriteTag, std::move(texture));

    return texture.get();
}




void RenderingModule::RenderTexture(SDL_Texture *texture, const ComponentTransform &transform) {
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

    SDL_RenderCopyExF(renderer, texture, nullptr, &destRect, transform.rotation, nullptr,
                      SDL_RendererFlip::SDL_FLIP_NONE);
}

