#pragma once
#include <string_view>
#include <logger/types.hpp>

class Logger {
public:
    Logger(const char* color);
    ~Logger();
    Logger& operator<<(const std::string_view& view);
    Logger& operator<<(const char* str);
    Logger& operator<<(bool b);
    Logger& operator<<(char ch);
    Logger& operator<<(unsigned char ch);
    Logger& operator<<(int num);
    Logger& operator<<(unsigned int num);
    Logger& operator<<(long num);
    Logger& operator<<(unsigned long num);
    Logger& operator<<(long long num);
    Logger& operator<<(unsigned long long num);
    Logger& operator<<(double num);
};

Logger INFO();
Logger DEBUG();
Logger INFO();
Logger WARN();
Logger ERROR();
Logger FATAL();