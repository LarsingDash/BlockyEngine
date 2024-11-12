//
// Created by hmkam on 12/11/2024.
//

#include "Logging.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std::chrono;

Logging::Logging(const std::string &filename) {
	logFile.open(filename, std::ios::app); // Opens file in append mode
	if (!logFile.is_open()) {
		std::cerr << "Error opening log file." << std::endl;
	} else {
		Log(INFO, "Logging started.");
	}
}

Logging::~Logging() { logFile.close(); }

void Logging::Log(const LogLevel level, const std::string &message) {
	auto logMessage = MakeTimeStamp();

	logMessage << "\t"
			<< levelToString(level) << "\t"
			<< message << std::endl;

	writeLog(logMessage);
}

std::string Logging::levelToString(LogLevel level) {
	switch (level) {
		case DEBUG:
			return "DEBUG";
		case INFO:
			return "INFO";
		case WARN:
			return "WARNING";
		case ERR:
			return "ERROR";
		default:
			return "UNKNOWN";
	}
}

// Format the time string, including milliseconds
std::stringstream Logging::MakeTimeStamp() {
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

void Logging::writeLog(const std::stringstream &logMessage) {
	if (LOG_TO_CONSOLE) {
		std::cout << logMessage.str();
	}

	// Output to log file
	if (logFile.is_open()) {
		logFile << logMessage.str();
		logFile.flush(); // Ensure immediate write to file
	}
}
