//
// Created by hmkam on 12/11/2024.
//

#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <sstream>
#include <glm/vec2.hpp>

// if logging is lagging the game don't set LOG_TO_CONSOLE 0, because it gives the biggest performers hit
#define LOG_TO_CONSOLE 1
#define LOG_TO_FILE 1

// length for function/class name that is reserved
// if length function/class name is > value, alignment
// of msg is offset by length function/class - value.
constexpr int MAX_FUNCTION_NAME_LENGTH = 15;
constexpr bool REMOVE_ARGS = true;
constexpr bool REMOVE_FUNCTION_NAME_FROM_CLASSES = true;
constexpr bool REMOVE_RETURN_TYPE = true;

// for function name only: __func__
#define BLOCKY_ENGINE_INFO(msg) bLogger.Log(LogLevel::INFO, __PRETTY_FUNCTION__, msg)
#define BLOCKY_ENGINE_DEBUG(msg) bLogger.Log(LogLevel::DEBUG, __PRETTY_FUNCTION__, msg)
#define BLOCKY_ENGINE_WARNING(msg) bLogger.Log(LogLevel::WARN, __PRETTY_FUNCTION__, msg)
#define BLOCKY_ENGINE_ERROR(msg) bLogger.Log(LogLevel::ERROR, __PRETTY_FUNCTION__, msg)

#define BLOCKY_ENGINE_DEBUG_STREAM(msg) bLogger.Log(LogLevel::DEBUG, __PRETTY_FUNCTION__, (std::stringstream() << msg).str())
#define BLOCKY_ENGINE_ERROR_STREAM(msg) bLogger.Log(LogLevel::ERROR, __PRETTY_FUNCTION__, (std::stringstream() << msg).str())

enum LogLevel {
	INFO,
	DEBUG,
	WARN,
	ERROR
};

class BLogger {
public:
	explicit BLogger(const std::string& filename);

	~BLogger();

	void Log(LogLevel level, const std::string& funcName = "", const std::string& message = "");
	void Log(LogLevel level, const std::string& funcName, const glm::vec2& message);
	void Log(LogLevel level, const std::string& funcName, const float& message);

private:
	std::ofstream _logFile; // File stream for the log file

	static std::string _levelToString(LogLevel level);

	static std::string _funcSignToString(std::string funcName);

	static std::stringstream _makeTimeStamp();

	void _writeLog(const std::stringstream& logMessage);
};

// Definition of global variable 'BLogger bLogger' in a header file should have an 'inline' specifier.
// Inline essentially tells the compiler that there MIGHT be multiple definitions,
//  but they all DO refer to the same instance.
// https://www.reddit.com/r/cpp_questions/comments/1ewgc22/how_do_inline_static_variables_work/
// This bLogger object is created so that the BLOCKY_ENGINE_ macros can be called without first
//  calling the constructor or having multiple BLogger objects.
inline BLogger bLogger("logfile.txt");

#endif //LOG_HPP
