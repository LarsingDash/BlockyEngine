//
// Created by 11896 on 19/11/2024.
//

#include "AnimationController.hpp"
#include <stdexcept>


AnimationController::AnimationController(GameObject& gameObject, const char* tag, AnimationRenderable& renderable)
		: Component(gameObject, tag), renderable(renderable) {}

void AnimationController::Start() {
}

void AnimationController::Update(float delta) {
	if (!isAnimating) {
		return;
	}

	auto animationIter = animations.find(currentAnimationName);
	if (animationIter == animations.end()) {
		return;
	}

	const Animation& animation = animationIter->second;

	frameTimer += delta;
	if (frameTimer >= frameDuration) {
		frameTimer -= frameDuration;

		//Update the current frame
		currentFrame++;
		if (currentFrame > animation.endFrame) {
			if (animation.looping) {
				currentFrame = animation.startFrame;
			} else {
				currentFrame = animation.endFrame;
				StopAnimation();
			}
		}

		//Update the renderable sourceRect to the current frame
		UpdateSourceRect();
	}
}


void AnimationController::End() {
	StopAnimation();
}

void AnimationController::SetFrameDuration(float duration) {
	frameDuration = duration;
}

void AnimationController::AddAnimation(const std::string& animationName, int startFrame, int endFrame, bool looping) {
	animations[animationName] = {startFrame, endFrame, looping};
}

void AnimationController::PlayAnimation(const std::string& animationName) {
	if (animations.find(animationName) == animations.end()) {
		throw std::runtime_error("Animation not found: " + animationName);
	}

	currentAnimationName = animationName;
	const Animation& animation = animations[animationName];
	currentFrame = animation.startFrame;
	isAnimating = true;

	UpdateSourceRect();
}

void AnimationController::StopAnimation() {
	isAnimating = false;
}

void AnimationController::UpdateSourceRect() {
	const SDL_Rect& frame = renderable.GetFrame(currentFrame);
	renderable.sourceRect = frame;
}

