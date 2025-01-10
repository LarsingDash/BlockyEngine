//
// Created by doguk on 11/28/2024.
//

#include "BLogger_Fixture.hpp"

TEST(BLogger_Fixture, Test_Logging) {
	bLogger.Log(LogLevel::INFO, "TestFunc", "Testing to see if GTest will Log!");
	EXPECT_EQ(1, 1);
}