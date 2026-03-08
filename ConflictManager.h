#pragma once
#include <string>

class ConflictManager {
public:
    std::string eventhappen;
    void declareWar(const std::string& attacker, const std::string& defender);
    void betrayAlliance(const std::string& attacker, const std::string& ally);
};
