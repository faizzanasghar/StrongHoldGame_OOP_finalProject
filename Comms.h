#pragma once
#include <string>

class Comms {
public:
    void sendMessage(const std::string& from, const std::string& to, const std::string& message);
    void receiveMessage(const std::string& player);
};
