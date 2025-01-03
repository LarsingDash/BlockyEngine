//
// Created by 11896 on 19/11/2024.
//

#include "AnimationController.hpp"

#include "gameObject/GameObject.hpp"
#include "components/renderables/AnimationRenderable.hpp"
#include "logging/BLogger.hpp"

AnimationController::AnimationController(GameObject* gameObject, const char* tag)
		: Component(gameObject, tag), _renderable(nullptr) {}

AnimationController::~AnimationController() {
	StopAnimation();
}

Component* AnimationController::_clone(const GameObject& parent) {
	auto clone = new AnimationController(*this);
	return clone;
}

void AnimationController::Start() {
	_renderable = gameObject->GetComponent<AnimationRenderable>();
}

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

void AnimationController::End() {}

void AnimationController::AddAnimation(const std::string& animationName,
									   int startFrame,
									   int endFrame,
									   float frameDuration,
									   bool looping) {
	_animations[animationName] = {startFrame, endFrame, looping, frameDuration};
}

bool AnimationController::PlayAnimation(const std::string& animationName) {
	//Check if the animation exists in the map
	auto it = _animations.find(animationName);
	if (it == _animations.end()) {
		std::string err("Animation not found: ");
		err += animationName;
		BLOCKY_ENGINE_ERROR(err);
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
	if (_renderable) _renderable->SetCurrentFrame(_currentFrame);
}

JSON_REGISTER_FROM(
		AnimationController,
		[](const nlohmann::json& json, AnimationController& other) {
			other._frameTimer = json.at("frameTimer").get<float>();
			other._currentFrame = json.at("currentFrame").get<int>();
			other._isAnimating = json.at("isAnimating").get<bool>();

			other._currentAnimationName = json.at("currentAnimationName").get<std::string>();
			for (const auto& [tag, animation]: json.at("animations").items()) {
				other._animations.emplace(tag, AnimationController::Animation{
						animation.at("startFrame").get<int>(),
						animation.at("endFrame").get<int>(),
						animation.at("looping").get<bool>(),
						animation.at("frameDuration").get<float>()
				});
			}

			auto it = other._animations.find(other._currentAnimationName);
			if (it != other._animations.end())
				other._currentAnimation = &it->second;
		}
)

JSON_REGISTER_TO(
		AnimationController,
		[](nlohmann::json& json, const AnimationController& other) {
			json["frameTimer"] = other._frameTimer;
			json["currentFrame"] = other._currentFrame;
			json["isAnimating"] = other._isAnimating;

			json["currentAnimationName"] = other._currentAnimationName;
			auto animations = nlohmann::json{};
			for (const auto& [tag, animation]: other._animations) {
				auto animJson = (nlohmann::ordered_json{
						{"startFrame",    animation.startFrame},
						{"endFrame",      animation.endFrame},
						{"looping",       animation.looping},
						{"frameDuration", animation.frameDuration}
				});
				animations[tag] = animJson;
			}
			json["animations"] = animations;
		}
)
