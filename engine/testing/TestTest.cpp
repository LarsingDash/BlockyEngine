//
// Created by doguk on 11/28/2024.
//

#include "TestTest.hpp"
TEST_F(TestTest, PrintQueue) {
	while (!testQueue.empty()) {
		std::cout << "Queue item: " << testQueue.front() << "\n";
		testQueue.pop();
	}
	std::cout << std::endl;
}

TEST_F(TestTest, ForceQuit) {
	EXPECT_EQ(testQueue.front(), 100) << "First index was: " << testQueue.front() << " Expected: 100";
}