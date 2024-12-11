//
// Created by 11896 on 07/12/2024.
//

#include "TimeUtil.hpp"

#include "logging/BLogger.hpp"

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
	std::string msg("Toggling fps counter to ");
	msg += std::to_string(_showFps);
	BLOCKY_ENGINE_DEBUG(msg);
	_showFps = !_showFps;
}

bool TimeUtil::IsFpsCounterEnabled() const {
	return _showFps;
}

void TimeUtil::SetGameSpeed(float speed) {
	if (speed > 0.0f) {
		_gameSpeed = speed;
		std::string msg("Game speed set to ");
		msg += std::to_string(_gameSpeed);
		msg += 'x';
		BLOCKY_ENGINE_DEBUG(msg);
	} else {
		BLOCKY_ENGINE_ERROR("Invalid game speed. Speed must be greater than 0.");
	}
}

float TimeUtil::GetGameSpeed() const {
	return _gameSpeed;
}

void TimeUtil::IncreaseGameSpeed() {
	if (BASE_GAME_SPEED_INDEX < static_cast<int>(GAME_SPEEDS.size()) - 1) {
		BASE_GAME_SPEED_INDEX++;
		_gameSpeed = GAME_SPEEDS[BASE_GAME_SPEED_INDEX];

		std::string msg("Game speed increased to: ");
		msg += std::to_string(_gameSpeed);
		msg += 'x';
		BLOCKY_ENGINE_DEBUG(msg);
	}
}

void TimeUtil::DecreaseGameSpeed() {
	if (BASE_GAME_SPEED_INDEX > 0) {
		BASE_GAME_SPEED_INDEX--;
		_gameSpeed = GAME_SPEEDS[BASE_GAME_SPEED_INDEX];

		std::string msg("Game speed decreased to: ");
		msg += std::to_string(_gameSpeed);
		msg += 'x';
		BLOCKY_ENGINE_DEBUG(msg);
	}
}

void TimeUtil::ResetGameSpeed() {
	BASE_GAME_SPEED_INDEX = 3;
	_gameSpeed = GAME_SPEEDS[BASE_GAME_SPEED_INDEX];

	std::string msg("Game speed reset to default: ");
	msg += std::to_string(_gameSpeed);
	msg += 'x';
	BLOCKY_ENGINE_DEBUG(msg);
}
