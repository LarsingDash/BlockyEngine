//
// Created by hmkam on 12/11/2024.
//

#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>

#define LOG_TO_CONSOLE 1
#define MAX_FUNCTION_NAME_LENGHT 15
#define LOG_FILE "logfile.txt"

// for function name only: __func__
#define BLOCKY_ENGINE_INFO(msg) bLogger.Log(LogLevel::INFO, __PRETTY_FUNCTION__, msg);
#define BLOCKY_ENGINE_DEBUG(msg) bLogger.Log(LogLevel::DEBUG, __PRETTY_FUNCTION__, msg);
#define BLOCKY_ENGINE_WARNING(msg) bLogger.Log(LogLevel::WARN, __PRETTY_FUNCTION__, msg);
#define BLOCKY_ENGINE_ERROR(msg) bLogger.Log(LogLevel::ERROR, __PRETTY_FUNCTION__, msg);

enum LogLevel {
    INFO,
    DEBUG,
    WARN,
    ERROR
};

class BLogger {
    public:
        explicit BLogger(const std::string &filename);

        ~BLogger();

        void Log(LogLevel level, const std::string &funcName = "", const std::string &message = "");

    private:
        std::ofstream _logFile; // File stream for the log file

        static std::string _LevelToString(LogLevel level);

        static std::string _FuncSignToString(std::string funcName);

        static std::stringstream _MakeTimeStamp();

        void _WriteLog(const std::stringstream &logMessage);
};

inline BLogger bLogger(LOG_FILE);

#endif //LOG_HPP