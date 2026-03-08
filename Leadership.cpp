#include "Leadership.h"
#include "Economy.h"
#include "Population.h"
#include <iostream>

Leadership::Leadership()
    : influence(50.0), taxRate(20.0) {}

Leadership::~Leadership() {}

void Leadership::validateInputs() {
    if (influence < 0 || taxRate < 0 || taxRate > 100) {
        std::cout << "Invalid leadership values" << std::endl;
    }
}

void Leadership::setTaxRate(double rate, Economy& economy, Population& population) {
    if (rate < 0 || rate > 100) {
        std::cout << "Invalid tax rate" << std::endl;
        return;
    }
    taxRate = rate;
    economy.generateIncome((int)(rate * 10.0));
    population.setEmployment(population.getEmployment() - rate * 0.1);
    validateInputs();
}

void Leadership::boostInfluence(double amount, Economy& economy) {
    if (amount < 0) {
        std::cout << "Invalid influence amount" << std::endl;
        return;
    }
    influence += amount;
    if (influence > 100.0) {
        influence = 100.0;
    }
    economy.generateIncome((int)(amount * 5.0));
    validateInputs();
}

void Leadership::implementWelfare(Population& population, Economy& economy) {
    population.setEmployment(population.getEmployment() + 5.0);
    economy.generateIncome(-100);
    influence += 10.0;
    if (influence > 100.0) {
        influence = 100.0;
    }
    validateInputs();
}

double Leadership::getInfluence() const {
    return influence;
}

double Leadership::getTaxRate() const {
    return taxRate;
}

void Leadership::saveState(std::ofstream& outFile) const {
    if (!outFile) {
        std::cout << "Failed to write to save file" << std::endl;
    } else {
        outFile << influence << " " << taxRate << std::endl;
    }
}

void Leadership::loadState(std::ifstream& inFile) {
    if (!inFile) {
        std::cout << "Failed to read from save file" << std::endl;
    } else {
        inFile >> influence >> taxRate;
        if (inFile.fail()) {
            std::cout << "Failed to parse save file" << std::endl;
        }
        validateInputs();
    }
}
