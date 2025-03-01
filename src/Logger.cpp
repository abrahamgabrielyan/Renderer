#include "Logger.hpp"

#include <iostream>

Logger::Logger() {
    logFile.open("renderer.log", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
    } else {
        logFile << "[INFO] Logger initialized." << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    if (logFile.is_open()) {
        logFile << "[" << level << "] " << message << std::endl;
    }
}

void Logger::logInfo(const std::string& message) {
    log("INFO", message);
}

void Logger::logWarning(const std::string& message) {
    log("WARNING", message);
}

void Logger::logError(const std::string& message) {
    log("ERROR", message);
}
