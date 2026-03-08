#pragma once
#include <string>

class TradeSystem {
public:
    std::string tradestatus;
    std::string smuggleststus;
    void offerTrade(const std::string& from, const std::string& to, const std::string& resource, int quantity);
    void attemptSmuggle(const std::string& from, const std::string& to, const std::string& resource);
};
