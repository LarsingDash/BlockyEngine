//
// Created by hmkam on 12/11/2024.
//

#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>

#define LOG_TO_CONSOLE 1
#define MAX_FUNCTION_NAME_LENGHT 15
#define LOG_FILE "logfile.txt"

// for function signature: __PRETTY_FUNCTION__
#define BLOCKY_ENGINE_INFO(msg) bLogger.Log(LogLevel::INFO, __func__, msg);
#define BLOCKY_ENGINE_DEBUG(msg) bLogger.Log(LogLevel::DEBUG, __func__, msg);
#define BLOCKY_ENGINE_WARNING(msg) bLogger.Log(LogLevel::WARN, __func__, msg);
#define BLOCKY_ENGINE_ERROR(msg) bLogger.Log(LogLevel::ERR, __func__, msg);

enum LogLevel {
    INFO,
    DEBUG,
    WARN,
    ERR
};

class BLogger {
    public:
        explicit BLogger(const std::string &filename);

        ~BLogger();

        void Log(LogLevel level, const std::string &funcName = "", const std::string &message = "");

    private:
        std::ofstream logFile; // File stream for the log file

        static std::string levelToString(LogLevel level);

        static std::string funcSignToString(std::string funcName);

        std::stringstream MakeTimeStamp();

        void writeLog(const std::stringstream &logMessage);
};

inline BLogger bLogger(LOG_FILE);

#endif //LOG_HPP
