//
// Created by 11896 on 07/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_
#define BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_

#include <chrono>
#include <vector>

class TimeUtil {
	public:
		static TimeUtil* CreateInstance();

		inline static TimeUtil& GetInstance() { return *_instance; }

		~TimeUtil() = default;

		TimeUtil(const TimeUtil& other) = delete;
		TimeUtil& operator=(const TimeUtil& other) = delete;
		TimeUtil(TimeUtil&& other) noexcept = delete;
		TimeUtil& operator=(TimeUtil&& other) noexcept = delete;

		[[nodiscard]] float GetElapsedTime() const;
		[[nodiscard]] float GetScaledDeltaTime() const;
		[[nodiscard]] float GetGameSpeed() const;
		[[nodiscard]] int GetFPS() const;
		[[nodiscard]] bool IsFpsCounterEnabled() const;
		float CalculateDeltaTime();
		void ToggleFpsCounter();
		void SetGameSpeed(float speed);
		void Reset();

		void IncreaseGameSpeed();
		void DecreaseGameSpeed();
		void ResetGameSpeed();
	private:
		TimeUtil();
		static TimeUtil* _instance;

		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		TimePoint _startTime;
		TimePoint _lastFrameTime;
		float _rawDeltaTime;
		float _scaledDeltaTime;
		float _gameSpeed = 1.0f;
		bool _showFps = false;

		std::vector<float> GAME_SPEEDS{0.125f, 0.25f, 0.5f, 1.0f, 1.5f, 2.0f, 5.0f, 10.0f};
		int BASE_GAME_SPEED_INDEX = 3;
};

#endif //BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_
