#include "Military.h"
#include "Population.h"
#include "Resources.h"
#include <iostream>

Military::Military()
    : soldierCount(100), strength(10.0), weaponTypes(4) {
    weaponStock = new int[weaponTypes];
    for (int i = 0; i < weaponTypes; i++) {
        weaponStock[i] = 50;
    }
}

Military::~Military() {
    delete[] weaponStock;
}

void Military::validateInputs() {
    if (soldierCount < 0 || strength < 0) {
        std::cout << "Negative military values" << std::endl;
        return;
    }
    for (int i = 0; i < weaponTypes; i++) {
        if (weaponStock[i] < 0) {
            std::cout << "Negative weapon stock" << std::endl;
        }
    }
}

void Military::recruitSoldiers(int number, Population& population) {
    if (number < 0 || number > population.getTotalPopulation()) {
        std::cout << "Invalid soldier count" << std::endl;
        return;
    }
    soldierCount += number;
    strength += number * 0.1;
    population.reducePopulation(number);
    validateInputs();
}

void Military::equipWeapons(int ironAmount, Resources& resources) {
    if (ironAmount < 0 || ironAmount > resources.getResource(Iron)) {
        std::cout << "Invalid or insufficient iron amount" << std::endl;
        return;
    }
    resources.consumeResources(0, 0, 0, ironAmount);
    for (int i = 0; i < weaponTypes; i++) {
        weaponStock[i] += (int)(ironAmount * 0.25);
    }
    strength += ironAmount * 0.05;
    validateInputs();
}

void Military::defendAttack(double attackStrength) {
    if (attackStrength < 0) {
        std::cout << "Invalid attack strength" << std::endl;
        return;
    }
    strength -= attackStrength * 0.5;
    if (strength < 0.0) {
        strength = 0.0;
    }
    soldierCount -= (int)(attackStrength * 2.0);
    if (soldierCount < 0) {
        soldierCount = 0;
    }
    validateInputs();
}

int Military::getSoldierCount() const {
    return soldierCount;
}

double Military::getStrength() const {
    return strength;
}

void Military::saveState(std::ofstream& outFile) const {
    if (!outFile) {
        std::cout << "Failed to write to save file" << std::endl;
    } else {
        outFile << soldierCount << " " << strength << " " << weaponTypes;
        for (int i = 0; i < weaponTypes; i++) {
            outFile << " " << weaponStock[i];
        }
        outFile << std::endl;
    }
}

void Military::loadState(std::ifstream& inFile) {
    if (!inFile)
        std::cout << "Failed to read from save file" << std::endl;
    else {
        inFile >> soldierCount >> strength >> weaponTypes;
        delete[] weaponStock;
        weaponStock = new int[weaponTypes];
        for (int i = 0; i < weaponTypes; i++) {
            inFile >> weaponStock[i];
        }
        if (inFile.fail()) {
            std::cout << "Failed to parse save file" << std::endl;
        }
        validateInputs();
    }
}
