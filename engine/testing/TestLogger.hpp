//
// Created by doguk on 10/27/2024.
//

#ifndef TESTLOGGER_HPP
#define TESTLOGGER_HPP
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

class TestLogger : public ::testing::EmptyTestEventListener {
	public:
		TestLogger() {
			//logger openen;
			testLogger.open(R"(../logs/test_logs.txt)");
		}

		void OnTestProgramStart(const ::testing::UnitTest& unitTest) override {
			if (!testLogger.is_open())
				throw std::runtime_error("File not found, or is not opened!");

			testLogger << "[TEST SUITE START] " << unitTest.current_test_case() <<
					   " Test start Timestamp: " << unitTest.start_timestamp()
					   << std::endl;
		}

		void OnTestProgramEnd(const ::testing::UnitTest& unitTest) override {
			if (!testLogger.is_open())
				throw std::runtime_error("File not found, or is not opened!");

			testLogger << "[TEST SUITE END] " << unitTest.current_test_case() <<
					   " Amount of test succes: " << unitTest.successful_test_count() <<
					   " Amount of test failures: " << unitTest.failed_test_count() << std::endl;
			testLogger.close();
		}

		void OnTestStart(const ::testing::TestInfo& testInfo) override {
			if (testLogger.is_open()) {
				testLogger << "[TEST START] " << testInfo.test_case_name() << "." << testInfo.name() << std::endl;
			}
		}

		void OnTestPartResult(const ::testing::TestPartResult& testPartResult) override {
			if (testLogger.is_open()) {
				testLogger << "[PART-RESULT] " <<
						   (testPartResult.failed() ? "FAILED" : "PASSED") << ": " <<
						   testPartResult.file_name() << ":" <<
						   testPartResult.line_number() << ": " <<
						   testPartResult.summary() << std::endl;
			}
		}

		void OnTestEnd(const ::testing::TestInfo& testInfo) override {
			if (testLogger.is_open()) {
				testLogger << "[END OF TEST] " << (testInfo.result()->Passed() ? "PASSED" : "FAILED") <<
						   ": " << testInfo.test_case_name() << "." <<
						   testInfo.name() << std::endl;
			}
		}

	private:
		std::ofstream testLogger;
};
#endif //TESTLOGGER_HPP