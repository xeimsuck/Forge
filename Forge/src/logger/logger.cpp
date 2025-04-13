#include "logger.hpp"
#include <iostream>


const char* DEBUG_COLOR = "\e[0;37m"; // WHITE
const char* INFO_COLOR  = "\e[0;37m"; // WHITE
const char* WARN_COLOR  = "\e[0;33m"; // YELLOW
const char* ERROR_COLOR = "\e[0;31m"; // RED
const char* FATAL_COLOR = "\e[0;31m"; // RED



Logger::Logger(const char* color){
    std::cout << color;
}

Logger::~Logger(){
    std::cout << INFO_COLOR << std::endl;
}

Logger& Logger::operator<<(const std::string_view& view){
    std::cout << view;
    return *this;
}


Logger DEBUG(){
    return Logger(DEBUG_COLOR);
}

Logger INFO(){
    return Logger(INFO_COLOR);
}

Logger WARN(){
    return Logger(WARN_COLOR);
}

Logger ERROR(){
    return Logger(ERROR_COLOR);
}

Logger FATAL(){
    return Logger(FATAL_COLOR);
}