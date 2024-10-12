//
// Created by 11896 on 12/10/2024.
//

#include <iostream>
#include "AnimatedSprite.hpp"
#include "../Texture.h"

AnimatedSprite::AnimatedSprite(const char* filePath, IRenderer* renderer, int frameWidth, int frameHeight, int rows, int columns)
        : currentFrame(0), elapsedTime(0.0f), isPlaying(false) {
    spritesheet = Texture::loadTextureFromFile(filePath, renderer->getSDLRenderer());

    if (spritesheet) {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < columns; ++col) {
                frames.push_back({col * frameWidth, row * frameHeight, frameWidth, frameHeight});
            }
        }
        std::cout << "Loaded " << frames.size() << " frames" << std::endl;
    } else {
        std::cerr << "Failed to load spritesheet: " << filePath << std::endl;
    }

    dstRect = {0, 0, frameWidth, frameHeight};
}

AnimatedSprite::~AnimatedSprite() {
    if (spritesheet) {
        SDL_DestroyTexture(spritesheet);
    }
}

void AnimatedSprite::update(float deltaTime) {
    if (isPlaying && !animations.empty() && !currentAnimationName.empty()) {
        elapsedTime += deltaTime;
        try {
            if (elapsedTime >= animations.at(currentAnimationName).getFrameTime()) {
                updateAnimationFrame();
                elapsedTime = 0.0f;
            }
        } catch (const std::out_of_range& e) {
            std::cerr << "Animation '" << currentAnimationName << "' not found." << std::endl;
            isPlaying = false;
        }
    }
}

void AnimatedSprite::updateAnimationFrame() {
    try {
        const Animation& currentAnimation = animations.at(currentAnimationName);
        int frameCount = currentAnimation.getEndFrame() - currentAnimation.getStartFrame() + 1;
        int relativeFrame = currentFrame - currentAnimation.getStartFrame();

        if (relativeFrame + 1 < frameCount) {
            currentFrame++;
        } else if (currentAnimation.isLooping()) {
            currentFrame = currentAnimation.getStartFrame();
        } else {
            isPlaying = false;
        }
    } catch (const std::out_of_range& e) {
        std::cerr << "Animation '" << currentAnimationName << "' not found." << std::endl;
        isPlaying = false;
    }
}

void AnimatedSprite::render(IRenderer* renderer) {
    if (spritesheet && !frames.empty() && currentFrame < frames.size()) {
        renderer->drawTexture(spritesheet, &frames[currentFrame], &dstRect);
    }
}

void AnimatedSprite::setPosition(int x, int y) {
    dstRect.x = x;
    dstRect.y = y;
}

void AnimatedSprite::addAnimation(const Animation& animation) {
    animations.emplace(animation.getName(), animation);
}

void AnimatedSprite::playAnimation(const std::string& name) {
    if (animations.find(name) != animations.end()) {
        currentAnimationName = name;
        currentFrame = animations.at(name).getStartFrame();
        isPlaying = true;
        elapsedTime = 0.0f;
    } else {
        std::cerr << "Animation not found: " << name << std::endl;
    }
}

void AnimatedSprite::stopAnimation() {
    isPlaying = false;
    elapsedTime = 0.0f;
}