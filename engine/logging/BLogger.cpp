//
// Created by hmkam on 12/11/2024.
//

#include "BLogger.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <glm/vec2.hpp>

BLogger::BLogger(const std::string& filename) {
	_logFile.open(filename, std::ios::out);
	if (!_logFile.is_open()) {
		std::cerr << "Error opening log file." << std::endl;
	}
	else {
		BLOCKY_ENGINE_INFO("Logging started.")
	}
}

BLogger::~BLogger() { _logFile.close(); }

void BLogger::Log(const LogLevel level, const std::string& funcName, const std::string& message) {
	auto logMessage = _makeTimeStamp();

	logMessage << "   "
		<< _levelToString(level) << "   "
		<< _funcSignToString(funcName) << "   "
		<< message;

	_writeLog(logMessage);
}

void BLogger::Log(LogLevel level, const std::string& funcName, const glm::vec2& message) {
	Log(level, funcName, "(" + std::to_string(message.x) + ", " + std::to_string(message.y) + ")");
}

void BLogger::Log(LogLevel level, const std::string& funcName, const float& message) {
	Log(level, funcName, "(" + std::to_string(message) + ")");
}

std::string BLogger::_levelToString(LogLevel level) {
	switch (level) {
		case DEBUG:
			return "DEBUG";
		case INFO:
			return "INFO ";
		case WARN:
			return "WARN ";
		case ERROR:
			return "ERROR";
		default:
			return "UNKNOWN";
	}
}

std::string BLogger::_funcSignToString(std::string funcName) {
	if constexpr (REMOVE_ARGS || REMOVE_FUNCTION_NAME_FROM_CLASSES || REMOVE_RETURN_TYPE) {
		size_t pos1, pos2;

		if constexpr (REMOVE_ARGS) {
			pos1 = funcName.rfind('(');
			if (pos1 != std::string::npos) {
				funcName = funcName.substr(0, pos1);
			}
		}

		if constexpr (REMOVE_FUNCTION_NAME_FROM_CLASSES) {
			if constexpr ((REMOVE_ARGS)) {
				pos1 = funcName.rfind("::");

				if (pos1 != std::string::npos) {
					funcName = funcName.substr(0, pos1);
				}
			}
			else {
				// temp remove args
				std::string tempFuncName;
				pos2 = funcName.rfind('(');
				if (pos2 != std::string::npos) {
					tempFuncName = funcName.substr(0, pos2);
				}

				// after temp remove args remove class from funcName
				pos1 = tempFuncName.rfind("::");

				// remove funtion beteween class and args
				if (pos1 != std::string::npos && pos2 != std::string::npos) {
					funcName = funcName.substr(0, pos1) + funcName.substr(pos2, funcName.length());
				}
			}
		}

		if constexpr (REMOVE_RETURN_TYPE) {
			if constexpr (!(REMOVE_ARGS)) {
				// temp remove args
				std::string tempFuncName;
				pos1 = funcName.rfind('(');
				if (pos1 != std::string::npos) {
					tempFuncName = funcName.substr(0, pos1);
				}

				// after temp remove args remove class from funcName
				pos1 = tempFuncName.rfind(' ');
			}
			else {
				pos1 = funcName.rfind(' ');
			}
			if (pos1 != std::string::npos) {
				funcName = funcName.substr(pos1 + 1);
			}
		}
	}

	// try to align all function names, without shorting function name
	if (funcName.size() < MAX_FUNCTION_NAME_LENGTH) {
		funcName.resize(MAX_FUNCTION_NAME_LENGTH, ' ');
	}
	return funcName;
}

// Format the time string, including milliseconds
std::stringstream BLogger::_makeTimeStamp() {
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

	uint16_t milliseconds = ms.count() % 1000;

	// Convert to time_t
	time_t tt = std::chrono::system_clock::to_time_t(now);
	// Get local time
	std::tm* tm = std::localtime(&tt);

	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << tm->tm_hour << ":"
		<< std::setw(2) << tm->tm_min << ":"
		<< std::setw(2) << tm->tm_sec << "."
		<< std::setw(3) << milliseconds;
	return ss;
}

void BLogger::_writeLog(const std::stringstream& logMessage) {
	if constexpr (LOG_TO_CONSOLE) {
		std::cout << logMessage.str() << std::endl;
	}

	if constexpr (LOG_TO_FILE) {
		// Output to log file
		if (_logFile.is_open()) {
			_logFile << logMessage.str() << '\n';
			_logFile.flush(); // Ensure immediate write to file
		}
	}
}
