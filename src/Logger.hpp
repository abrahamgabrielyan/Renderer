#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <mutex>
#include <string>

class Logger {
public:
    static Logger& getInstance();
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

private:
    std::ofstream logFile;
    std::mutex mutex;
    Logger();
    ~Logger();
    void log(const std::string& level, const std::string& message);
};

#endif // LOGGER_HPP
