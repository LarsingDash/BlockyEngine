//
// Created by doguk on 11/28/2024.
//

#include "TestTest.hpp"

/**
 * @brief  This is a test function, basically a macro calling TEST_FIXTURE
 * You can also call TEST, a Fixture is just a TestClass that we use between multiple
 * .cpp files for testing different parts.
 * It's structured as such: The TestClass, Name of the test function.
 */
TEST_F(TestTest, PrintQueue) {
	while (!testQueue.empty()) {
		std::cout << "Queue item: " << testQueue.front() << "\n";
		testQueue.pop();
	}
	std::cout << std::endl;
}

/**
 * @brief As per usual, testing has the EXPECT and ASSERT keywords.
 * It is recommended to use EXPECT, only when a test has to run with errors you might consider using ASSERT.
 */
TEST_F(TestTest, ForceQuit) {
	//Has both float and double, otherwise it will default to int I believe.
	//Equals
	EXPECT_EQ(0, 0);
	//Not Equals
	EXPECT_NE(0, 10);

	//Assert has the same ones
	ASSERT_EQ(testQueue.front(), 100) << "First index was: " << testQueue.front() << " Expected: 100";
}