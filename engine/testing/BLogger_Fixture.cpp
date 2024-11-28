//
// Created by doguk on 11/28/2024.
//

#include "BLogger_Fixture.hpp"
TEST(BLogger_Fixture, Test_Without_File) {
	BLogger b_logger("");

	b_logger.Log(INFO, "TEST");
}