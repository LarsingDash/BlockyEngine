//
// Created by 11896 on 07/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_
#define BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_

#include <chrono>
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

	private:
		TimeUtil();
		static TimeUtil* _instance;

		void _reset();

		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		TimePoint _startTime;
		TimePoint _lastFrameTime;
		float _rawDeltaTime;
		float _scaledDeltaTime;
		float _gameSpeed = 1.0f;
		bool _showFps = false;
};

#endif //BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_
