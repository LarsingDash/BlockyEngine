//
// Created by 11896 on 07/12/2024.
//
#include "TimeUtil.hpp"

TimeUtil* TimeUtil::_instance{nullptr};

TimeUtil* TimeUtil::CreateInstance() {
	auto instance = new TimeUtil();
	_instance = instance;
	return instance;
}

TimeUtil::TimeUtil()
		: startTime{Clock::now()},
		  lastFrameTime{Clock::now()},
		  lastDeltaTime{0.0f} {}

void TimeUtil::reset() {
	startTime = Clock::now();
	lastFrameTime = Clock::now();
	lastDeltaTime = 0.0f;
}

float TimeUtil::calculateDeltaTime() {
	auto now = Clock::now();
	lastDeltaTime = std::chrono::duration<float>(now - lastFrameTime).count();
	lastFrameTime = now;
	return lastDeltaTime;
}

float TimeUtil::getElapsedTime() const {
	auto now = Clock::now();
	return std::chrono::duration<float>(now - startTime).count();
}

int TimeUtil::getFPS() const {
	return (lastDeltaTime > 0.0f) ? static_cast<int>(1.0f / lastDeltaTime) : 0;
}

