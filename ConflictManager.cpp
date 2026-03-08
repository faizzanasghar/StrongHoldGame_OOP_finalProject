#include "ConflictManager.h"
#include <iostream>

void ConflictManager::declareWar(const std::string& attacker, const std::string& defender) {
    std::cout << attacker << " has declared war on " << defender << "!" << std::endl;
    std::cout << defender << " is attacked!." << std::endl;
}

void ConflictManager::betrayAlliance(const std::string& attacker, const std::string& ally) {
    std::cout << attacker << " has betrayed their alliance with " << ally << "!" << std::endl;
    eventhappen = "Broked.";
}
