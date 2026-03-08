#include "Economy.h"
#include "Resources.h"
#include "Population.h"
#include <iostream>

Economy::Economy()
    : wealth(1000.0), employmentRate(70.0) {}

Economy::~Economy() {}

void Economy::validateInputs() {
    if (wealth < 0 || employmentRate < 0 || employmentRate > 100) {
        std::cout << "Invalid economy values" << std::endl;
    }
}

void Economy::generateIncome(int population) {
    wealth += population;
    if (wealth < 0) {
        wealth = 0;
    }
    validateInputs();
}

void Economy::tradeResources(int giveType, int giveAmount, int receiveType, int receiveAmount, Resources& resources) {
    if (giveType < 0 || giveType > 3 || receiveType < 0 || receiveType > 3 || giveAmount < 0 || receiveAmount < 0) {
        std::cout << "Invalid trade parameters" << std::endl;
        return;
    }
    resources.tradeResources(giveType, giveAmount, receiveType, receiveAmount);
    wealth += receiveAmount * 10 - giveAmount * 5;
    if (wealth < 0) {
        wealth = 0;
    }
    validateInputs();
}

void Economy::adjustEmployment(double rate, Population& population) {
    if (rate < 0 || rate > 100) {
        std::cout << "Invalid employment rate" << std::endl;
        return;
    }
    employmentRate = rate;
    population.setEmployment(rate);
    wealth -= (int)(rate * 10.0);
    if (wealth < 0) {
        wealth = 0;
    }
    validateInputs();
}

double Economy::getWealth() const {
    return wealth;
}

double Economy::getEmploymentRate() const {
    return employmentRate;
}

void Economy::saveState(std::ofstream& outFile) const {
    if (!outFile) {
        std::cout << "Failed to write to save file" << std::endl;
    } else {
        outFile << wealth << " " << employmentRate << std::endl;
    }
}

void Economy::loadState(std::ifstream& inFile) {
    if (!inFile) {
        std::cout << "Failed to read from save file" << std::endl;
    } else {
        inFile >> wealth >> employmentRate;
        if (inFile.fail()) {
            std::cout << "Failed to parse save file" << std::endl;
        }
        validateInputs();
    }
}
