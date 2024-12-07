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


		float GetElapsedTime() const;
		int GetFPS() const;
		void ToggleFpsCounter();
		bool IsFpsCounterEnabled() const;

		float CalculateDeltaTime();
	private:
		TimeUtil();
		static TimeUtil* _instance;

		void _reset();

		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		TimePoint _startTime;
		TimePoint _lastFrameTime;
		float _lastDeltaTime;
		bool _showFps = false;
};

#endif //BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_
