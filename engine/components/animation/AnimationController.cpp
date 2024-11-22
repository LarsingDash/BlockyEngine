//
// Created by 11896 on 19/11/2024.
//

#include "AnimationController.hpp"


AnimationController::AnimationController(GameObject& gameObject, const char* tag, AnimationRenderable& renderable)
		: Component(gameObject, tag), renderable(renderable) {}

void AnimationController::Start() {};


//Updates the animation state
void AnimationController::Update(float delta) {
	//Skips update if animation is not active
	if (!isAnimating) return;

	//Find the current animation in the unordered map
	auto it = animations.find(currentAnimationName);
	if (it == animations.end()) return;

	const Animation& animation = it->second;

	frameTimer += delta;
	while (frameTimer >= frameDuration) {
		frameTimer -= frameDuration;

		//Move to the next frame
		currentFrame++;
		if (currentFrame > animation.endFrame) {
			if (animation.looping) {
				//Loop back to the start frame if the animation is looping
				currentFrame = animation.startFrame;
			} else {
				//Stop animation if its a non-looping animation
				currentFrame = animation.endFrame;
				StopAnimation();
				break;
			}
		}
		//Update the source rect for the current frame
		UpdateSourceRect();
	}
}


void AnimationController::End() {
	StopAnimation();
}

//Sets the duration for each frame in the animation
void AnimationController::SetFrameDuration(float duration) {
	frameDuration = duration;
}

//Adds a new animation to the controller
void AnimationController::AddAnimation(const std::string& animationName, int startFrame, int endFrame, bool looping) {
	animations[animationName] = {startFrame, endFrame, looping};
}

// Starts playing the specified animation by tag
bool AnimationController::PlayAnimation(const std::string& animationName) {

	//Check if the animation exists in the map
	if (animations.find(animationName) == animations.end()) {
		std::cerr << "Animation not found: " << animationName << std::endl;
		return false;
	}

	currentAnimationName = animationName;
	const Animation& animation = animations[animationName];
	currentFrame = animation.startFrame;
	isAnimating = true;

	UpdateSourceRect();
	return true;
}

//Stops the currently playing animation
void AnimationController::StopAnimation() {
	isAnimating = false;
}

//Updates the source rectangle of the renderable to match the current frame
void AnimationController::UpdateSourceRect() {
	renderable.SetCurrentFrame(currentFrame);
}

