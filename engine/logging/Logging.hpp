//
// Created by hmkam on 12/11/2024.
//

#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>

#define LOG_TO_CONSOLE 1

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERR
};

class Logging {
    public:
        explicit Logging(const std::string &filename);

        ~Logging();

        void Log(LogLevel level, const std::string &message);

    private:
        std::ofstream logFile; // File stream for the log file

        static std::string levelToString(LogLevel level);

        std::stringstream MakeTimeStamp();

        void writeLog(const std::stringstream &logMessage);
};

#endif //LOG_HPP
