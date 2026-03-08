#pragma once
#include <fstream>

class Population {
private:
    int totalPopulation;
    double growthRate;
    double healthStatus;
    double revoltRisk;
    double employment;
    void validateInputs();
public:
    Population();
    ~Population();
    void updatePopulation(double foodSupply, double employment, double shelter);
    void triggerDisease(double severity);
    int checkRevolt();
    int getTotalPopulation() const;
    double getRevoltRisk() const;
    void saveState(std::ofstream& outFile) const;
    void loadState(std::ifstream& inFile);
    void setEmployment(double employment);
    double getEmployment() const;
    void reducePopulation(int number);
};
