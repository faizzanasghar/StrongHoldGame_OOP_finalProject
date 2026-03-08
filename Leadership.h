#pragma once
#include <fstream>

class Economy;
class Population;

class Leadership {
private:
    double influence;
    double taxRate;
    void validateInputs();
public:
    Leadership();
    ~Leadership();
    void setTaxRate(double rate, Economy& economy, Population& population);
    void boostInfluence(double amount, Economy& economy);
    void implementWelfare(Population& population, Economy& economy);
    double getInfluence() const;
    double getTaxRate() const;
    void saveState(std::ofstream& outFile) const;
    void loadState(std::ifstream& inFile);
};
