//
//  logger.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#ifndef logger_hpp
#define logger_hpp

#include <string>

class Logger {

    public:
        enum class LogLevel { DBG, INFO, WARNING, ERROR };

        void debug(std::string msg);
        void info(std::string msg);
        void warning(std::string msg);
        void error(std::string msg);

        static void Initialize(LogLevel logLevel);
        static Logger* GetInstance();
        
    protected:
        static Logger* logger;
        Logger(LogLevel logLevel);

    private:
        LogLevel logLevel;
        void print(std::string msg, LogLevel logLevel);
};

#endif /* logger_hpp */
