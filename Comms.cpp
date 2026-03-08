#include "Comms.h"
#include <iostream>

void Comms::sendMessage(const std::string& from, const std::string& to, const std::string& message) {
    std::cout << "[" << from << " -> " << to << "]: " << message << std::endl;
}

void Comms::receiveMessage(const std::string& player) {
    std::cout << player << " is checking messages." << std::endl;
}
