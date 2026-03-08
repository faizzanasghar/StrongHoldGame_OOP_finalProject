#pragma once
#include <fstream>

class Economy;
class Population;

class Bank {
private:
    double reserves;
    double loanAmount;
    void validateInputs();
public:
    Bank();
    ~Bank();
    void takeLoan(double amount, Economy& economy, Population& population);
    void makeInvestment(double amount, Economy& economy, Population& population);
    void repayLoan(double amount, Economy& economy);
    double getReserves() const;
    double getLoanAmount() const;
    void saveState(std::ofstream& outFile) const;
    void loadState(std::ifstream& inFile);
};
