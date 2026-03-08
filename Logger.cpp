#include "Logger.h"
#include <iostream>

void Logger::logEvent(const std::string& type, const std::string& data) {
    std::cout << "[" << type << "] " << data << std::endl;
}
