#include "SocialStructure.h"
#include "Population.h"
#include "Economy.h"
#include <iostream>

SocialStructure::SocialStructure()
    : morale(50.0), education(50.0) {}

SocialStructure::~SocialStructure() {}

void SocialStructure::validateInputs() {
    if (morale < 0 || education < 0) {
        std::cout << "Negative social values" << std::endl;
    }
}

void SocialStructure::improveMorale(double amount, Population& population, Economy& economy) {
    if (amount < 0) {
        std::cout << "Invalid morale amount" << std::endl;
        return;
    }
    morale += amount;
    if (morale > 100.0) {
        morale = 100.0;
    }
    population.setEmployment(population.getEmployment() + amount * 0.1);
    economy.generateIncome((int)(amount * 10.0));
    validateInputs();
}

void SocialStructure::improveEducation(double amount, Population& population, Economy& economy) {
    if (amount < 0) {
        std::cout << "Invalid education amount" << std::endl;
        return;
    }
    education += amount;
    if (education > 100.0) {
        education = 100.0;
    }
    population.setEmployment(population.getEmployment() + amount * 0.05);
    economy.generateIncome((int)(amount * 5.0));
    validateInputs();
}

double SocialStructure::getMorale() const {
    return morale;
}

double SocialStructure::getEducation() const {
    return education;
}

void SocialStructure::saveState(std::ofstream& outFile) const {
    if (!outFile) {
        std::cout << "Failed to write to save file" << std::endl;
    } else {
        outFile << morale << " " << education << std::endl;
    }
}

void SocialStructure::loadState(std::ifstream& inFile) {
    if (!inFile) {
        std::cout << "Failed to read from save file" << std::endl;
    } else {
        inFile >> morale >> education;
        if (inFile.fail()) {
            std::cout << "Failed to parse save file" << std::endl;
        }
        validateInputs();
    }
}
