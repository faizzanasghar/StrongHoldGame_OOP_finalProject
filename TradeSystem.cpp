#include "TradeSystem.h"
#include <iostream>

void TradeSystem::offerTrade(const std::string& from, const std::string& to, const std::string& resource, int quantity) {
    std::cout << from << " offers " << quantity << " units of " << resource << " to " << to << "." << std::endl;
    int choice, priceperun, tp;
    std::cout << "Player " << to << " Want Trade? (1=yes,0=No)." << std::endl;
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Trade attempted ! " << std::endl;
        std::cout << "Enter Perunit price of Resource?" << std::endl;
        std::cin >> priceperun;
        tp = priceperun * quantity;
        std::cout << "Total Ammount " << tp << "$ is Paid.Happy Trade !" << std::endl;
    } else {
        std::cout << to << " rejected to trade." << std::endl;
    }
}

void TradeSystem::attemptSmuggle(const std::string& from, const std::string& to, const std::string& resource) {
    int choice, ammount;
    std::string event;
    std::cout << from << " attempts to smuggle " << resource << " to " << to << std::endl;
    std::cout << "Try Succeded ? (1=Yes,0=Not) :" << std::endl;
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Enter Ammount Paid ?" << std::endl;
        std::cin >> ammount;
        std::cout << "Ammount Paid to Player " << from << " For Smuggling!" << std::endl;
    } else {
        std::cout << "1.Police Raid \n2.Spy information\n3.Mismanagement" << std::endl;
        std::cin >> event;
        std::cout << "Smuggling Failed due to " << event << std::endl;
    }
}
