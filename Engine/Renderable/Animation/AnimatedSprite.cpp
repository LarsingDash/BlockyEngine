#include "AnimatedSprite.hpp"
#include "../Texture.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(const char* filePath, IRenderer* renderer, AnimationController* controller, int frameWidth, int frameHeight, int width, int height)
        : spritesheet(nullptr), animationController(controller), dstRect({0, 0, width, height}) {
    spritesheet = Texture::loadTextureFromFile(filePath, renderer->getSDLRenderer());

    if (spritesheet) {
        loadFrames(frameWidth, frameHeight);
        std::cout << "Loaded " << frames.size() << " frames" << std::endl;
    } else {
        std::cerr << "Failed to load spritesheet: " << filePath << std::endl;
    }
}

AnimatedSprite::~AnimatedSprite() {
    if (spritesheet) {
        SDL_DestroyTexture(spritesheet);
    }
}

void AnimatedSprite::loadFrames(int frameWidth, int frameHeight) {
    int textureWidth, textureHeight;
    SDL_QueryTexture(spritesheet, nullptr, nullptr, &textureWidth, &textureHeight);

    int rows = textureHeight / frameHeight;
    int columns = textureWidth / frameWidth;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            frames.push_back({col * frameWidth, row * frameHeight, frameWidth, frameHeight});
        }
    }
}

void AnimatedSprite::update(float deltaTime) {
    animationController->update(deltaTime);
}

void AnimatedSprite::render(IRenderer* renderer) {
    if (spritesheet && !frames.empty()) {
        int currentFrame = animationController->getCurrentFrame();
        if (currentFrame < frames.size()) {
            renderer->drawTexture(spritesheet, &frames[currentFrame], &dstRect);
        }
    }
}

void AnimatedSprite::setPosition(int x, int y) {
    dstRect.x = x;
    dstRect.y = y;
}
