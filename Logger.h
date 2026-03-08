#pragma once
#include <string>

class Logger {
public:
    void logEvent(const std::string& type, const std::string& data);
};
