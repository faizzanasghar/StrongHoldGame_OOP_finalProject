#include "Population.h"
#include <iostream>

Population::Population()
    : totalPopulation(1000), growthRate(0.02), healthStatus(80.0), revoltRisk(10.0), employment(70.0) {}

Population::~Population() {}

void Population::validateInputs() {
    if (totalPopulation < 0 || healthStatus < 0 || revoltRisk < 0 || employment < 0 || employment > 100) {
        std::cout << "Negative or invalid population values" << std::endl;
    }
}

void Population::updatePopulation(double foodSupply, double employment, double shelter) {
    if (foodSupply < 0 || employment < 0 || shelter < 0) {
        std::cout << "Negative supply values are invalid" << std::endl;
        return;
    }
    growthRate = (foodSupply * 0.01 + employment * 0.005 + shelter * 0.005) - 0.01;
    totalPopulation += (int)(totalPopulation * growthRate);
    healthStatus = healthStatus + foodSupply * 0.1 + shelter * 0.05 - 5.0;
    if (healthStatus > 100.0) {
        healthStatus = 100.0;
    }
    revoltRisk = revoltRisk + (100.0 - healthStatus) * 0.02 + (100.0 - employment) * 0.03;
    if (revoltRisk > 100.0) {
        revoltRisk = 100.0;
    }
    validateInputs();
}

void Population::triggerDisease(double severity) {
    if (severity < 0 || severity > 100) {
        std::cout << "Invalid disease severity" << std::endl;
        return;
    }
    healthStatus = healthStatus - severity;
    if (healthStatus < 0.0) {
        healthStatus = 0.0;
    }
    totalPopulation -= (int)(totalPopulation * (severity / 200.0));
    revoltRisk = revoltRisk + severity * 0.1;
    if (revoltRisk > 100.0) {
        revoltRisk = 100.0;
    }
    validateInputs();
}

int Population::checkRevolt() {
    return (revoltRisk > 80.0) ? 1 : 0;
}

int Population::getTotalPopulation() const {
    return totalPopulation;
}

double Population::getRevoltRisk() const {
    return revoltRisk;
}

void Population::saveState(std::ofstream& outFile) const {
    if (!outFile) {
        std::cout << "Failed to write to save file" << std::endl;
    } else {
        outFile << totalPopulation << " " << growthRate << " " << healthStatus << " " << revoltRisk << " " << employment << std::endl;
    }
}

void Population::loadState(std::ifstream& inFile) {
    if (!inFile) {
        std::cout << "Failed to read from save file" << std::endl;
    } else {
        inFile >> totalPopulation >> growthRate >> healthStatus >> revoltRisk >> employment;
        if (inFile.fail()) {
            std::cout << "Failed to parse save file" << std::endl;
        }
        validateInputs();
    }
}

void Population::setEmployment(double employment) {
    if (employment < 0 || employment > 100) {
        std::cout << "Invalid employment" << std::endl;
        return;
    }
    this->employment = employment;
    revoltRisk += (100.0 - employment) * 0.03;
    if (revoltRisk > 100.0) {
        revoltRisk = 100.0;
    }
    validateInputs();
}

double Population::getEmployment() const {
    return employment;
}

void Population::reducePopulation(int number) {
    if (number < 0 || number > totalPopulation) {
        std::cout << "Invalid population reduction" << std::endl;
        return;
    }
    totalPopulation -= number;
    validateInputs();
}
