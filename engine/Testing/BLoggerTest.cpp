//
// Created by hmkam on 13/11/2024.
//

#include "BLoggerTest.hpp"

#include "../../engine/logging/BLogger.hpp"
#include <string>

void _TestBLoggerFunc(const std::string &str) {
	BLOCKY_ENGINE_DEBUG(str)
}

class BloggerClass {
	public:
		static void FuncBloggerClass(const std::string &str) {
			BLOCKY_ENGINE_DEBUG(str)
		}
};

void BLoggerTest::Test() {
	BLOCKY_ENGINE_DEBUG("Debugging information, in BLoggerTest::Test()");

	for (int i = 0; i < 5; i++) {
		BLOCKY_ENGINE_INFO("Program update: " + std::to_string(i));

		//delay
		for (int j = 0; j < 100000000; j++) { if (i == j) { j = i; } }
	}

	BLOCKY_ENGINE_ERROR("An error occurred.");
	BLOCKY_ENGINE_WARNING("An warning occurred.");

	_TestBLoggerFunc("Debugging information, in TestBLoggerFunc()");

	BloggerClass::FuncBloggerClass("Debugging information, in BloggerClass::FuncBloggerClass()");
}
