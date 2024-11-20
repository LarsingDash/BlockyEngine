//
// Created by 11896 on 19/11/2024.
//
 #include "Animator.hpp"

//Animator::Animator()
//		: _currentAnimation(nullptr), _currentFrame(0), _elapsedTime(0.0f) {}
//
//void Animator::SetAnimation(const Animation* animation) {
//	_currentAnimation = animation;
//	_currentFrame = animation ? animation->frameRange.first : 0;
//	_elapsedTime = 0.0f;
//}
//
//void Animator::Update(float deltaTime) {
//	if (_currentAnimation) {
//		_elapsedTime += deltaTime;
//
//		float frameDuration = 0.1f;
//		if (_elapsedTime >= frameDuration) {
//			_elapsedTime = 0.0f;
//			_currentFrame++;
//
//			if (_currentFrame > _currentAnimation->frameRange.second) {
//				_currentFrame = _currentAnimation->isLooping
//								? _currentAnimation->frameRange.first
//								: _currentAnimation->frameRange.second;
//			}
//		}
//	}
//}
//
//int Animator::GetCurrentFrame() const {
//	return _currentFrame;
//}