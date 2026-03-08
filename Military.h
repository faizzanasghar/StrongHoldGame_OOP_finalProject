#pragma once
#include <fstream>

class Population;
class Resources;

class Military {
private:
    int soldierCount;
    double strength;
    int* weaponStock;
    int weaponTypes;
    void validateInputs();
public:
    Military();
    ~Military();
    void recruitSoldiers(int number, Population& population);
    void equipWeapons(int ironAmount, Resources& resources);
    void defendAttack(double attackStrength);
    int getSoldierCount() const;
    double getStrength() const;
    void saveState(std::ofstream& outFile) const;
    void loadState(std::ifstream& inFile);
};
