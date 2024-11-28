//
// Created by doguk on 11/28/2024.
//
#include "testing/TestLogger.hpp"
#include <gtest/gtest.h>

int main(int argc, char** argv) {
	::testing::InitGoogleTest();
	::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

	listeners.Append(new TestLogger);
	int result = RUN_ALL_TESTS();

	return result;
}