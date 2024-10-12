#include "AnimationController.hpp"
#include <iostream>

AnimationController::AnimationController()
        : currentAnimationName(""), currentFrame(0), elapsedTime(0), isPlaying(false) {}

void AnimationController::addAnimation(const Animation& animation) {
    animations.emplace(animation.getName(), animation);
}

void AnimationController::playAnimation(const std::string& name) {
    if (animations.find(name) != animations.end()) {
        currentAnimationName = name;
        currentFrame = animations.at(name).getStartFrame();
        isPlaying = true;
        elapsedTime = 0.0f;
    } else {
        std::cerr << "Animation not found: " << name << std::endl;
    }
}

void AnimationController::stopAnimation() {
    isPlaying = false;
    elapsedTime = 0.0f;
}

void AnimationController::update(float deltaTime) {
    if (isPlaying && !currentAnimationName.empty()) {
        elapsedTime += deltaTime;
        const Animation& currentAnimation = animations.at(currentAnimationName);
        if (elapsedTime >= currentAnimation.getFrameTime()) {
            updateAnimationFrame(currentAnimation);
            elapsedTime = 0.0f;
        }
    }
}

int AnimationController::getCurrentFrame() const {
    return currentFrame;
}

bool AnimationController::isAnimationPlaying() const {
    return isPlaying;
}

void AnimationController::updateAnimationFrame(const Animation& animation) {
    int startFrame = animation.getStartFrame();
    int endFrame = animation.getEndFrame();

    if (currentFrame < endFrame) {
        currentFrame++;
    } else if (animation.isLooping()) {
        currentFrame = startFrame;
    } else {
        isPlaying = false;
    }
}
