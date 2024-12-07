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

		void reset();
		float calculateDeltaTime();
		float getElapsedTime() const;
		int getFPS() const;
		void toggleFpsCounter();
		bool isFpsCounterEnabled() const;

	private:
		TimeUtil();

		static TimeUtil* _instance;

		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		TimePoint startTime;
		TimePoint lastFrameTime;
		float lastDeltaTime;
		bool showFps;
};

#endif //BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_
