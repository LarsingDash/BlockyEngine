//
// Created by 11896 on 07/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_
#define BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_

#include <chrono>

class TimeUtil {
	public:
		TimeUtil();
		void reset();
		float getElapsedTime() const;
		float calculateDeltaTime();
		int getFPS() const;


	private:
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		TimePoint startTime;
		TimePoint lastFrameTime;
		float lastDeltaTime;
};

#endif //BLOCKYENGINE_ENGINE_UTILITIES_TIMEUTIL_HPP_
