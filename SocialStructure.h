#pragma once
#include <fstream>

class Population;
class Economy;

class SocialStructure {
private:
    double morale;
    double education;
    void validateInputs();
public:
    SocialStructure();
    ~SocialStructure();
    void improveMorale(double amount, Population& population, Economy& economy);
    void improveEducation(double amount, Population& population, Economy& economy);
    double getMorale() const;
    double getEducation() const;
    void saveState(std::ofstream& outFile) const;
    void loadState(std::ifstream& inFile);
};
