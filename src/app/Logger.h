#pragma once

#include <Arduino.h>

namespace eps32s3_firmware {

enum class LogLevel : uint8_t {
    Error = 0,
    Warning = 1,
    Info = 2,
    Debug = 3
};

class Logger {
public:
    static void begin(LogLevel level) { level_ = level; }

    static void error(const char* message) { log(LogLevel::Error, message); }
    static void warning(const char* message) { log(LogLevel::Warning, message); }
    static void info(const char* message) { log(LogLevel::Info, message); }
    static void debug(const char* message) { log(LogLevel::Debug, message); }

    static void log(LogLevel level, const char* message) {
        if (level > level_) {
            return;
        }

        Serial0.printf("[%lu][%s] %s\r\n",
                       static_cast<unsigned long>(millis()),
                       levelName(level),
                       message);
    }

private:
    static const char* levelName(LogLevel level) {
        switch (level) {
            case LogLevel::Error: return "ERROR";
            case LogLevel::Warning: return "WARN";
            case LogLevel::Info: return "INFO";
            case LogLevel::Debug: return "DEBUG";
        }
        return "LOG";
    }

    static inline LogLevel level_ = LogLevel::Info;
};

}  // namespace eps32s3_firmware