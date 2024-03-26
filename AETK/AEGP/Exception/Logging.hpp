/*****************************************************************//**
 * \file   Logging.hpp
 * \brief  Logging utility for AEGP
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/

#ifndef LOGGING_HPP
#define LOGGING_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"

// Define log levels
enum class LogLevel
{
    Error,
    Warning,
    Info,
    Debug
};

// Forward declaration of the Logger class
class Logger;
// You MUST Enable Logging from AE Settings to use/see the logs
// Logging macros for convenience
#define LOG_ERROR(subsystem, message)                                          \
    Logger::Log(subsystem, LogLevel::Error, message)
#define LOG_WARNING(subsystem, message)                                        \
    Logger::Log(subsystem, LogLevel::Warning, message)
#define LOG_INFO(subsystem, message)                                           \
    Logger::Log(subsystem, LogLevel::Info, message)
#define LOG_DEBUG(subsystem, message)                                          \
    Logger::Log(subsystem, LogLevel::Debug, message)

class Logger
{
  public:
    // Static log function used by macros
    static void Log(const std::string &subsystem, LogLevel level,
                    const std::string &message)
    {
        // Here, you can direct log messages to the standard logging
        // implementation or a custom implementation if set by the user.
        if (customLogger)
        {
            customLogger->logImpl(subsystem, level, message);
        }
        else
        {
            UtilitySuite6().writeToDebugLog(subsystem, ToString(level), message);
        }
    }

    // Function to set a custom logger
    static void SetCustomLogger(Logger *logger) { customLogger = logger; }

  protected:
    // Virtual function for implementation in custom loggers
    virtual void logImpl(const std::string &subsystem, LogLevel level,
                         const std::string &message) = 0;

  private:
    static Logger *customLogger; // Pointer to a custom logger, if set

    static std::string ToString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Error:
            return "ERROR";
        case LogLevel::Warning:
            return "WARNING";
        case LogLevel::Info:
            return "INFO";
        case LogLevel::Debug:
            return "DEBUG";
        default:
            return "UNKNOWN";
        }
    }
};

// Definition of the static member
Logger *Logger::customLogger = nullptr;

#endif // LOGGING_HPP
