#pragma once
#include <string_view>
#include <logger/types.hpp>

class Logger {
public:
    Logger(const char* color);
    ~Logger();
    Logger& operator<<(const std::string_view& view);
};

Logger INFO();
Logger DEBUG();
Logger INFO();
Logger WARN();
Logger ERROR();
Logger FATAL();