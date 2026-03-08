#include "EventHandler.h"
#include "Population.h"
#include "Resources.h"
#include "Military.h"
#include "Economy.h"
#include "Leadership.h"
#include "Bank.h"
#include <iostream>

EventHandler::EventHandler() : lastEventType(-1) {}
EventHandler::~EventHandler() {}

void EventHandler::validateInputs() {
    if (lastEventType < -1)
        std::cout << "Invalid event type" << std::endl;
}

void EventHandler::triggerEvent(int eventType, Population& population, Resources& resources, Military& military, Economy& economy, Leadership& leadership, Bank& bank) {
    if (eventType < 0 || eventType > 3) {
        std::cout << "Invalid event type" << std::endl;
        return;
    }
    lastEventType = eventType;
    if (eventType == 0) {
        population.triggerDisease(30.0);
        resources.consumeResources(50, 0, 0, 0);
    } else if (eventType == 1) {
        resources.gatherResources(100, 50, 50, 20);
        economy.generateIncome(500);
    } else if (eventType == 2) {
        population.setEmployment(population.getEmployment() - 10.0);
        military.defendAttack(20.0);
    } else if (eventType == 3) {
        economy.tradeResources(0, 50, 1, 30, resources);
        bank.makeInvestment(200.0, economy, population);
    }
    validateInputs();
}

int EventHandler::getLastEventType() const {
    return lastEventType;
}

void EventHandler::saveState(std::ofstream& outFile) const {
    if (!outFile)
        std::cout << "Failed to write to save file" << std::endl;
    else
        outFile << lastEventType << std::endl;
}

void EventHandler::loadState(std::ifstream& inFile) {
    if (!inFile)
        std::cout << "Failed to read from save file" << std::endl;
    else {
        inFile >> lastEventType;
        if (inFile.fail())
            std::cout << "Failed to parse save file" << std::endl;
        validateInputs();
    }
}
