//
// Created by hmkam on 13/11/2024.
//

#include "BLoggerTest.hpp"

#include <chrono>

#include "../../engine/logging/BLogger.hpp"
#include <string>
#include <thread>

void TestBLoggerFunc(const std::string &testStr = "") {
	BLOCKY_ENGINE_DEBUG("Debugging information, in TestBLoggerFunc(const std::string& testStr = "")" + testStr)
}

class BloggerClass {
	public:
		static void FuncBloggerClass() {
			BLOCKY_ENGINE_DEBUG("Debugging information, in BloggerClass::FuncBloggerClass()")
			_funcBloggerClass();
		}

	private:
		static void _funcBloggerClass(const std::string &testStr = "") {
			BLOCKY_ENGINE_DEBUG(
				"Debugging information, in BloggerClass::_funcBloggerClass(const std::string& testStr = "")"+ testStr)
		}
};

void BLoggerTest::Test() {
	BLOCKY_ENGINE_DEBUG("Debugging information, in BLoggerTest::Test()");

	for (int i = 0; i < 5; i++) {
		BLOCKY_ENGINE_INFO("Program update: " + std::to_string(i));

		std::this_thread::sleep_for(std::chrono::microseconds(300));

		for (int j = 0; j < 100000000; j++) { if (i == j) { j = i; } }
	}

	BLOCKY_ENGINE_ERROR("An error occurred.");
	BLOCKY_ENGINE_WARNING("An warning occurred.");

	TestBLoggerFunc();
	BloggerClass::FuncBloggerClass();
}
