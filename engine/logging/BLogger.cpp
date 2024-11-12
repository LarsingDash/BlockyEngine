//
// Created by hmkam on 12/11/2024.
//

#include "BLogger.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std::chrono;

BLogger::BLogger(const std::string &filename) {
	logFile.open(filename, std::ios::app); // Opens file in append mode
	if (!logFile.is_open()) {
		std::cerr << "Error opening log file." << std::endl;
	} else {
		Log(INFO, "Logging started.");
	}
}

BLogger::~BLogger() { logFile.close(); }


void BLogger::Log(const LogLevel level, const std::string &funcName, const std::string &message) {
	auto logMessage = MakeTimeStamp();

	logMessage << "   "
			<< levelToString(level) << "   "
			<< funcSignToString(funcName) << "   "
			<< message << std::endl;

	writeLog(logMessage);
}

std::string BLogger::levelToString(LogLevel level) {
	switch (level) {
		case DEBUG:
			return "DEBUG";
		case INFO:
			return "INFO ";
		case WARN:
			return "WARN ";
		case ERR:
			return "ERR  ";
		default:
			return "UNKNOWN";
	}
}

std::string BLogger::funcSignToString(std::string funcName) {
	// //todo: uncomment when calling Log(...) with function signature: __PRETTY_FUNCTION__
	//
	// // remove args
	// size_t pos = funcName.rfind('(');
	// if (pos != std::string::npos) {
	// 	funcName = funcName.substr(0, pos);
	// }
	//
	// // remove function name if class
	// pos = funcName.rfind("::");
	// if (pos != std::string::npos) {
	// 	funcName = funcName.substr(0, pos);
	// }
	//
	// // remove return type
	// pos = funcName.rfind(' ');
	// if (pos != std::string::npos) {
	// 	funcName = funcName.substr(pos + 1);
	// }

	if (funcName.size() < MAX_FUNCTION_NAME_LENGHT) {
		funcName.resize(MAX_FUNCTION_NAME_LENGHT, ' ');
	}
	return funcName;
}

// Format the time string, including milliseconds
std::stringstream BLogger::MakeTimeStamp() {
	auto now = system_clock::now();
	auto ms = duration_cast<milliseconds>(now.time_since_epoch());

	uint16_t milliseconds = ms.count() % 1000;

	// Convert to time_t
	time_t tt = system_clock::to_time_t(now);
	// Get local time
	std::tm *tm = std::localtime(&tt);

	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << tm->tm_hour << ":"
			<< std::setw(2) << tm->tm_min << ":"
			<< std::setw(2) << tm->tm_sec << "."
			<< std::setw(3) << milliseconds;
	return ss;
}

void BLogger::writeLog(const std::stringstream &logMessage) {
	if (LOG_TO_CONSOLE) {
		std::cout << logMessage.str();
	}

	// Output to log file
	if (logFile.is_open()) {
		logFile << logMessage.str();
		logFile.flush(); // Ensure immediate write to file
	}
}
