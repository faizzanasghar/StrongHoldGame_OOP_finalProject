#pragma once
#include <string>

class AllianceManager {
public:
    std::string statusalliance;
    void formAlliance(const std::string& player1, const std::string& player2);
    void breakAlliance(const std::string& player1, const std::string& player2);
    void getAllianceStatus(const std::string& player1, const std::string& player2);
};
