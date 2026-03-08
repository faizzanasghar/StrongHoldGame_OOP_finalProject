#pragma once
#include <fstream>

class Resources {
private:
    int* resourceQuantities;
    int resourceCount;
    void validateInputs();
public:
    Resources();
    ~Resources();
    void gatherResources(int food, int wood, int stone, int iron);
    void consumeResources(int food, int wood, int stone, int iron);
    void tradeResources(int giveType, int giveAmount, int receiveType, int receiveAmount);
    int getResource(int type) const;
    void saveState(std::ofstream& outFile) const;
    void loadState(std::ifstream& inFile);
};
