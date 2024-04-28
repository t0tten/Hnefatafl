//
//  logger.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include "logger.hpp"
#include <iostream>

Logger::Logger(LogLevel logLevel) {
    this->logLevel = logLevel;
}

void Logger::debug(std::string msg) { this->print("DEBUG: " + msg, LogLevel::DBG); }
void Logger::info(std::string msg) { this->print("INFO: " + msg, LogLevel::INFO); }
void Logger::warning(std::string msg) { this->print("WARNING: " + msg, LogLevel::WARNING); }
void Logger::error(std::string msg) { this->print("ERROR: " + msg, LogLevel::ERROR); }

void Logger::print(std::string msg, LogLevel logLevel) {
    if (this->logLevel <= logLevel) {
        std::cout << msg << std::endl;
    }
}

Logger* Logger::logger= nullptr;;
Logger* Logger::GetInstance()
{
    if (logger == nullptr)
    {
        throw "ERROR: LogLevel is not setup!";
    }
    return logger;
}
void Logger::Initialize(LogLevel logLevel)
{
    if (logger == nullptr)
    {
        logger = new Logger(logLevel);
    }
}
