#pragma once
#include <fstream>

class Resources;
class Population;

class Economy {
private:
    double wealth;
    double employmentRate;
    void validateInputs();
public:
    Economy();
    ~Economy();
    void generateIncome(int population);
    void tradeResources(int giveType, int giveAmount, int receiveType, int receiveAmount, Resources& resources);
    void adjustEmployment(double rate, Population& population);
    double getWealth() const;
    double getEmploymentRate() const;
    void saveState(std::ofstream& outFile) const;
    void loadState(std::ifstream& inFile);
};
