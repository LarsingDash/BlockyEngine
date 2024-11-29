//
// Created by 11896 on 19/11/2024.
//
#include "AnimationController.hpp"

#include "logging/BLogger.hpp"

AnimationController::AnimationController(GameObject* gameObject, const char* tag, AnimationRenderable& renderable)
		: Component(gameObject, tag), _renderable(renderable) {}

Component* AnimationController::clone() {
	auto clone = new AnimationController(*this);
	return clone;
}

void AnimationController::Start() {}

void AnimationController::Update(float delta) {
	//Skips update if animation is not active
	if (!_isAnimating || !_currentAnimation) return;

	_frameTimer += delta;
	while (_frameTimer >= _currentAnimation->frameDuration) {
		_frameTimer -= _currentAnimation->frameDuration;

		//Move to the next frame
		_currentFrame++;
		if (_currentFrame > _currentAnimation->endFrame) {
			if (_currentAnimation->looping) {
				//Loop back to the start frame if the animation is looping
				_currentFrame = _currentAnimation->startFrame;
			} else {
				//Stop animation if it's a non-looping animation
				_currentFrame = _currentAnimation->endFrame;
				StopAnimation();
				break;
			}
		}
		//Update the source rect for the current frame
		_updateSourceRect();
	}
}

void AnimationController::End() {
	StopAnimation();
}

void AnimationController::AddAnimation(const std::string& animationName, int startFrame, int endFrame, float frameDuration, bool looping) {
	_animations[animationName] = {startFrame, endFrame, looping, frameDuration};
}

bool AnimationController::PlayAnimation(const std::string& animationName) {
	//Check if the animation exists in the map
	auto it = _animations.find(animationName);
	if (it == _animations.end()) {
		std::string err ("Animation not found: ");
		err += animationName;
		BLOCKY_ENGINE_ERROR(err)
		return false;
	}

	_currentAnimationName = animationName;
	_currentAnimation = &it->second;  //Cache pointer to current animation
	_currentFrame = _currentAnimation->startFrame;
	_frameTimer = 0.0f;
	_isAnimating = true;

	_updateSourceRect();
	return true;
}

void AnimationController::StopAnimation() {
	_isAnimating = false;
	_currentAnimation = nullptr;  //Set cached animation to nullptr
}

void AnimationController::_updateSourceRect() {
	_renderable.SetCurrentFrame(_currentFrame);
}
