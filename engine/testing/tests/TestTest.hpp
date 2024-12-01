//
// Created by doguk on 11/28/2024.
//

#ifndef BLOCKYENGINE_ENGINE_TESTING_TESTTEST_HPP_
#define BLOCKYENGINE_ENGINE_TESTING_TESTTEST_HPP_

#include <gtest/gtest.h>
#include <queue>

/**
 * @brief This is the test class and should always inherit from ::testing::Test
 * The class is always protected to use the functions but also its variables.
 * If you can't use the variable, then look through here and see if it's not in another qualifier (public, private).
 */
class TestTest : public ::testing::Test {
	protected:
		std::queue<int> testQueue{};

		//Everything within here gets setup PER test
		//Be careful with SetUp(), because its not Setup(), for some reason its PascalCase
		void SetUp() override {
			testQueue.push(9);
			testQueue.push(2);
			testQueue.push(1);
			testQueue.push(99);
		}

		void TearDown() override {
			std::cout << testQueue.empty() << std::endl;
		}
};

#endif //BLOCKYENGINE_ENGINE_TESTING_TESTTEST_HPP_