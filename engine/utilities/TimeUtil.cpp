//
// Created by 11896 on 07/12/2024.
//

#include "TimeUtil.hpp"

TimeUtil::TimeUtil() : startTime{Clock::now()}, lastFrameTime{Clock::now()} {}

void TimeUtil::reset() {
	startTime = Clock::now();
	lastFrameTime = Clock::now();
}

float TimeUtil::getElapsedTime() const {
	auto now = Clock::now();
	return std::chrono::duration<float>(now - startTime).count();
}

float TimeUtil::calculateDeltaTime() {
	auto now = Clock::now();
	float deltaTime = std::chrono::duration<float>(now - lastFrameTime).count();
	lastFrameTime = now;
	return deltaTime;
}