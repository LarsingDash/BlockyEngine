//
// Created by doguk on 11/28/2024.
//

#ifndef BLOCKYENGINE_ENGINE_TESTING_TESTTEST_HPP_
#define BLOCKYENGINE_ENGINE_TESTING_TESTTEST_HPP_

#include <gtest/gtest.h>
#include <queue>

class TestTest : public ::testing::Test {

	protected:
		std::queue<int> testQueue{};

		void SetUp() override {
			testQueue.push(9);
			testQueue.push(2);
			testQueue.push(1);
			testQueue.push(99);
		}
};

#endif //BLOCKYENGINE_ENGINE_TESTING_TESTTEST_HPP_