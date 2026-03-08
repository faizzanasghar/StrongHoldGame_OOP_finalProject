#include "AllianceManager.h"
#include <iostream>

void AllianceManager::formAlliance(const std::string& player1, const std::string& player2) {
    std::cout << player1 << " and " << player2 << " formed an alliance." << std::endl;
    statusalliance = "Formed";
}

void AllianceManager::breakAlliance(const std::string& player1, const std::string& player2) {
    std::cout << player1 << " broke alliance with " << player2 << "." << std::endl;
    statusalliance = "Broken";
}

void AllianceManager::getAllianceStatus(const std::string& player1, const std::string& player2) {
    std::cout << "Alliance status between " << player1 << " and " << player2 << " is " << statusalliance << std::endl;
}
