#include "Bank.h"
#include "Economy.h"
#include "Population.h"
#include <iostream>

Bank::Bank()
    : reserves(5000.0), loanAmount(0.0) {}

Bank::~Bank() {}

void Bank::validateInputs() {
    if (reserves < 0 || loanAmount < 0) {
        std::cout << "Invalid bank values" << std::endl;
    }
}

void Bank::takeLoan(double amount, Economy& economy, Population& population) {
    if (amount < 0 || amount > reserves) {
        std::cout << "Invalid or insufficient loan amount" << std::endl;
        return;
    }
    loanAmount += amount;
    reserves -= amount;
    economy.generateIncome((int)amount);
    population.setEmployment(population.getEmployment() + amount * 0.001);
    validateInputs();
}

void Bank::makeInvestment(double amount, Economy& economy, Population& population) {
    if (amount < 0 || amount > reserves) {
        std::cout << "Invalid or insufficient investment amount" << std::endl;
        return;
    }
    reserves -= amount;
    economy.generateIncome((int)(amount * 1.5));
    population.setEmployment(population.getEmployment() + amount * 0.002);
    validateInputs();
}

void Bank::repayLoan(double amount, Economy& economy) {
    if (amount < 0 || amount > loanAmount) {
        std::cout << "Invalid repayment amount" << std::endl;
        return;
    }
    loanAmount -= amount;
    reserves += amount;
    economy.generateIncome(-(int)(amount * 1.1));
    validateInputs();
}

double Bank::getReserves() const {
    return reserves;
}

double Bank::getLoanAmount() const {
    return loanAmount;
}

void Bank::saveState(std::ofstream& outFile) const {
    if (!outFile) {
        std::cout << "Failed to write to save file" << std::endl;
    } else {
        outFile << reserves << " " << loanAmount << std::endl;
    }
}

void Bank::loadState(std::ifstream& inFile) {
    if (!inFile) {
        std::cout << "Failed to read from save file" << std::endl;
    } else {
        inFile >> reserves >> loanAmount;
        if (inFile.fail()) {
            std::cout << "Failed to parse save file" << std::endl;
        }
        validateInputs();
    }
}
