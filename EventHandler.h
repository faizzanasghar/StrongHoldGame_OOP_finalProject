#pragma once
#include <fstream>

class Population;
class Resources;
class Military;
class Economy;
class Leadership;
class Bank;

class EventHandler {
private:
    int lastEventType;
    void validateInputs();
public:
    EventHandler();
    ~EventHandler();
    void triggerEvent(int eventType, Population& population, Resources& resources, Military& military, Economy& economy, Leadership& leadership, Bank& bank);
    int getLastEventType() const;
    void saveState(std::ofstream& outFile) const;
    void loadState(std::ifstream& inFile);
};
