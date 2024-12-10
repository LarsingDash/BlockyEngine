//
// Created by 11896 on 07/12/2024.
//
#include <iostream>
#include "TimeUtil.hpp"

TimeUtil* TimeUtil::_instance{nullptr};

TimeUtil* TimeUtil::CreateInstance() {
	auto instance = new TimeUtil();
	_instance = instance;
	return instance;
}

TimeUtil::TimeUtil()
		: _startTime{Clock::now()},
		  _lastFrameTime{Clock::now()},
		  _rawDeltaTime{0.0f},
		  _scaledDeltaTime{0.0f},
		  _gameSpeed{1.0f} {}

void TimeUtil::Reset() {
	_startTime = Clock::now();
	_lastFrameTime = Clock::now();
	_rawDeltaTime = 0.0f;
	_scaledDeltaTime = 0.0f;
}

float TimeUtil::CalculateDeltaTime() {
	auto now = Clock::now();
	_rawDeltaTime = std::chrono::duration<float>(now - _lastFrameTime).count();
	_lastFrameTime = now;

	_scaledDeltaTime = _rawDeltaTime * _gameSpeed;
	return _scaledDeltaTime;
}

float TimeUtil::GetScaledDeltaTime() const {
	return _scaledDeltaTime;
}

float TimeUtil::GetElapsedTime() const {
	auto now = Clock::now();
	return std::chrono::duration<float>(now - _startTime).count();
}

int TimeUtil::GetFPS() const {
	return (_rawDeltaTime > 0.0f) ? static_cast<int>(1.0f / _rawDeltaTime) : 0;
}

void TimeUtil::ToggleFpsCounter() {
	std::cout << "Toggling fps counter to " << _showFps << std::endl;
	_showFps = !_showFps;
}

bool TimeUtil::IsFpsCounterEnabled() const {
	return _showFps;
}

void TimeUtil::SetGameSpeed(float speed) {
	if (speed > 0.0f) {
		_gameSpeed = speed;
		std::cout << "Game speed set to " << _gameSpeed << "x" << std::endl;
	} else {
		std::cerr << "Invalid game speed. Speed must be greater than 0." << std::endl;
	}
}

float TimeUtil::GetGameSpeed() const {
	return _gameSpeed;
}

