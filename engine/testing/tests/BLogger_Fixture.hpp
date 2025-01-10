//
// Created by doguk on 11/28/2024.
//

#ifndef BLOCKYENGINE_ENGINE_TESTING_BLOGGER_FIXTURE_HPP_
#define BLOCKYENGINE_ENGINE_TESTING_BLOGGER_FIXTURE_HPP_

#include <gtest/gtest.h>

#include "logging/BLogger.hpp"

class BLogger_Fixture : public ::testing::Test {
	protected:
		BLogger_Fixture() {
			b_logger_ = std::make_unique<BLogger>("");
		}

		std::unique_ptr<BLogger> b_logger_;
};

#endif //BLOCKYENGINE_ENGINE_TESTING_BLOGGER_FIXTURE_HPP_