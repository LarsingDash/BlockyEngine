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
		  _lastDeltaTime{0.0f} {}

void TimeUtil::_reset() {
	_startTime = Clock::now();
	_lastFrameTime = Clock::now();
	_lastDeltaTime = 0.0f;
}

float TimeUtil::CalculateDeltaTime() {
	auto now = Clock::now();
	_lastDeltaTime = std::chrono::duration<float>(now - _lastFrameTime).count();
	_lastFrameTime = now;
	return _lastDeltaTime;
}

float TimeUtil::GetElapsedTime() const {
	auto now = Clock::now();
	return std::chrono::duration<float>(now - _startTime).count();
}

int TimeUtil::GetFPS() const {
	return (_lastDeltaTime > 0.0f) ? static_cast<int>(1.0f / _lastDeltaTime) : 0;
}

void TimeUtil::ToggleFpsCounter() {
	std::cout << "Toggling fps counter to " << _showFps << std::endl;
	_showFps = !_showFps;
}

bool TimeUtil::IsFpsCounterEnabled() const {
	return _showFps;
}
