#include"Header.h"
#include<iostream>
#include<fstream>
#include<string>
Bank::Bank()
{
    reserves = 5000.0;
    loanAmount = 0.0;
}
Bank::~Bank()
{

}
void Bank::validateInputs()
{
    if (reserves < 0 || loanAmount < 0)
    {
        cout << "Invalid bank values" << endl;
    }
}
void Bank::takeLoan(double amount, Economy& economy, Population& population)
{
    if (amount < 0 || amount > reserves)
    {
        cout << "Invalid or insufficient loan amount" << endl;
        return;
    }
    loanAmount += amount;
    reserves -= amount;
    economy.generateIncome((int)amount);
    population.setEmployment(population.getEmployment() + amount * 0.001);
    validateInputs();
}
void Bank::makeInvestment(double amount, Economy& economy, Population& population)
{
    if (amount < 0 || amount > reserves)
    {
        cout << "Invalid or insufficient investment amount" << endl;
        return;
    }
    reserves -= amount;
    economy.generateIncome((int)(amount * 1.5));
    population.setEmployment(population.getEmployment() + amount * 0.002);
    validateInputs();
}
void Bank::repayLoan(double amount, Economy& economy)
{
    if (amount < 0 || amount > loanAmount)
    {
        cout << "Invalid repayment amount" << endl;
        return;
    }
    loanAmount -= amount;
    reserves += amount;
    economy.generateIncome(-(int)(amount * 1.1));
    validateInputs();
}
double Bank::getReserves() const
{
    return reserves;
}
double Bank::getLoanAmount() const
{
    return loanAmount;
}
void Bank::saveState(ofstream& outFile) const
{
    if (!outFile)
    {
        cout << "Failed to write to save file" << endl;
    }
    else
    {
        outFile << reserves << " " << loanAmount << endl;
    }
}
void Bank::loadState(ifstream& inFile)
{
    if (!inFile)
    {
        cout << "Failed to read from save file" << endl;
    }
    else
    {
        inFile >> reserves >> loanAmount;
        if (inFile.fail())
        {
            cout << "Failed to parse save file" << endl;
        }
        validateInputs();
    }
}
//    Communication 
void comms::sendMessage(string from, string to, string message)
{
    cout << "[" << from << " -> " << to << "]: " << message << endl;
}
void comms::receiveMessage(string player)
{
    cout << player << " is checking messages." << endl;
}
//     Economy

Economy::Economy()
{
    wealth = 1000.0;
    employmentRate = 70.0;
}
Economy::~Economy()
{

}
void Economy::validateInputs()
{
    if (wealth < 0 || employmentRate < 0 || employmentRate > 100)
    {
        cout << "Invalid economy values" << endl;
    }
}
void Economy::generateIncome(int population)
{
    wealth += population;
    if (wealth < 0)
    {
        wealth = 0;
    }
    validateInputs();
}
void Economy::tradeResources(int giveType, int giveAmount, int receiveType, int receiveAmount, Resources& resources)
{
    if (giveType < 0 || giveType > 3 || receiveType < 0 || receiveType > 3 || giveAmount < 0 || receiveAmount < 0)
    {
        cout << "Invalid trade parameters" << endl;
        return;
    }
    resources.tradeResources(giveType, giveAmount, receiveType, receiveAmount);
    wealth += receiveAmount * 10 - giveAmount * 5;
    if (wealth < 0)
    {
        wealth = 0;
    }
    validateInputs();
}
void Economy::adjustEmployment(double rate, Population& population)
{
    if (rate < 0 || rate > 100)
    {
        cout << "Invalid employment rate" << endl;
        return;
    }
    employmentRate = rate;
    population.setEmployment(rate);
    wealth -= (int)(rate * 10.0);
    if (wealth < 0)
    {
        wealth = 0;
    }
    validateInputs();
}
double Economy::getWealth() const
{
    return wealth;
}
double Economy::getEmploymentRate() const
{
    return employmentRate;
}
void Economy::saveState(ofstream& outFile) const
{
    if (!outFile)
    {
        cout << "Failed to write to save file" << endl;
    }
    else
    {
        outFile << wealth << " " << employmentRate << endl;
    }
}
void Economy::loadState(ifstream& inFile)
{
    if (!inFile)
    {
        cout << "Failed to read from save file" << endl;
    }
    else
    {
        inFile >> wealth >> employmentRate;
        if (inFile.fail())
        {
            cout << "Failed to parse save file" << endl;
        }
        validateInputs();
    }
}
//Event Handler


EventHandler::EventHandler() : lastEventType(-1) {}
EventHandler::~EventHandler() {}
void EventHandler::validateInputs() {
    if (lastEventType < -1)
        cout << "Invalid event type" << endl;
}
void EventHandler::triggerEvent(int eventType, Population& population, Resources& resources, Military& military, Economy& economy, Leadership& leadership, Bank& bank) {
    if (eventType < 0 || eventType > 3) {
        cout << "Invalid event type" << endl;
        return;
    }
    lastEventType = eventType;
    if (eventType == 0) {
        population.triggerDisease(30.0);
        resources.consumeResources(50, 0, 0, 0);
    }
    else if (eventType == 1) {
        resources.gatherResources(100, 50, 50, 20);
        economy.generateIncome(500);
    }
    else if (eventType == 2) {
        population.setEmployment(population.getEmployment() - 10.0);
        military.defendAttack(20.0);
    }
    else if (eventType == 3) {
        economy.tradeResources(0, 50, 1, 30, resources);
        bank.makeInvestment(200.0, economy, population);
    }
    validateInputs();
}
int EventHandler::getLastEventType() const {
    return lastEventType;
}
void EventHandler::saveState(ofstream& outFile) const {
    if (!outFile)
        cout << "Failed to write to save file" << endl;
    else
        outFile << lastEventType << endl;
}
void EventHandler::loadState(ifstream& inFile) {
    if (!inFile)
        cout << "Failed to read from save file" << endl;
    else {
        inFile >> lastEventType;
        if (inFile.fail())
            cout << "Failed to parse save file" << endl;
        validateInputs();
    }
}

//  Military  
Military::Military()
{
    soldierCount = 100;
    strength = 10.0;
    weaponTypes = 4;

    weaponStock = new int[weaponTypes];
    for (int i = 0; i < weaponTypes; i++)
    {
        weaponStock[i] = 50;
    }
}

Military::~Military()
{
    delete[] weaponStock;
}
void Military::validateInputs()
{
    if (soldierCount < 0 || strength < 0)
    {
        cout << "Negative military values" << endl;
        return;
    }
    for (int i = 0; i < weaponTypes; i++)
    {
        if (weaponStock[i] < 0)
        {
            cout << "Negative weapon stock" << endl;
        }
    }
}
void Military::recruitSoldiers(int number, Population& population)
{
    if (number < 0 || number > population.getTotalPopulation())
    {
        cout << "Invalid soldier count" << endl;
        return;
    }
    soldierCount += number;
    strength += number * 0.1;
    population.reducePopulation(number);
    validateInputs();
}
void Military::equipWeapons(int ironAmount, Resources& resources)
{
    if (ironAmount < 0 || ironAmount > resources.getResource(3))
    {
        cout << "Invalid or insufficient iron amount" << endl;
        return;
    }
    resources.consumeResources(0, 0, 0, ironAmount);
    for (int i = 0; i < weaponTypes; i++)
    {
        weaponStock[i] += (int)(ironAmount * 0.25);
    }
    strength += ironAmount * 0.05;
    validateInputs();
}
void Military::defendAttack(double attackStrength)
{
    if (attackStrength < 0)
    {
        cout << "Invalid attack strength" << endl;
        return;
    }
    strength -= attackStrength * 0.5;
    if (strength < 0.0)
    {
        strength = 0.0;
    }
    soldierCount -= (int)(attackStrength * 2.0);
    if (soldierCount < 0)
    {
        soldierCount = 0;
    }
    validateInputs();
}
int Military::getSoldierCount() const
{
    return soldierCount;
}
double Military::getStrength() const
{
    return strength;
}
void Military::saveState(ofstream& outFile) const
{
    if (!outFile)
    {
        cout << "Failed to write to save file" << endl;
    }
    else
    {
        outFile << soldierCount << " " << strength << " " << weaponTypes;
        for (int i = 0; i < weaponTypes; i++)
        {
            outFile << " " << weaponStock[i];
        }
        outFile << endl;
    }
}
void Military::loadState(ifstream& inFile)
{
    if (!inFile)
        cout << "Failed to read from save file" << endl;
    else
    {
        inFile >> soldierCount >> strength >> weaponTypes;
        delete[] weaponStock;
        weaponStock = new int[weaponTypes];
        for (int i = 0; i < weaponTypes; i++)
        {
            inFile >> weaponStock[i];
        }
        if (inFile.fail())
        {
            cout << "Failed to parse save file" << endl;
        }
        validateInputs();
    }
}
//  Alliance

void AllianceManager::formAlliance(string player1, string player2)
{
    cout << player1 << " and " << player2 << " formed an alliance." << endl;
    statusalliance = "Formed";
}

void AllianceManager::breakAlliance(string player1, string player2)
{
    cout << player1 << " broke alliance with " << player2 << "." << endl;
    statusalliance = "Broken";
}

void AllianceManager::getAllianceStatus(string player1, string player2)
{
    cout << "Alliance status between " << player1 << " and " << player2 << " is " << statusalliance << endl;
}


void TradeSystem::offerTrade(string from, string to, string resource, int quantity)
{

    cout << from << " offers " << quantity << " units of " << resource << " to " << to << "." << endl;
    int choice, priceperun, tp;
    {
        cout << "Player " << to << "Want Trade? (1=yes,0=No)." << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Trade attempted ! " << endl;
            cout << "Enter Perunit price of Resource?" << endl;
            cin >> priceperun;
            tp = priceperun * quantity;
            cout << "Total Ammount " << tp << "$ is Paid.Happy Trade !" << endl;
        }
        else
        {
            cout << to << " rejected to trade." << endl;
        }
    }
}

void TradeSystem::attemptSmuggle(string from, string to, string resource)
{
    int choice, ammount;
    string event;
    cout << from << " attempts to smuggle " << resource << " to " << to << endl;
    cout << "Try Succeded ? (1=Yes,0=Not) :" << endl;
    cin >> choice;
    if (choice == 1)
    {
        cout << "Enter Ammount Paid ?" << endl;
        cin >> ammount;
        cout << "Ammount Paid to Player " << from << " For Smuggling!" << endl;
    }
    else
    {

        cout << "1.Police Raid \n2.Spy information\n3.Mismanagement" << endl;
        cin >> event;
        cout << "Smuggling Failed due to " << event << endl;
    }

}


void ConflictManager::declareWar(string attacker, string defender)
{
    cout << attacker << " has declared war on " << defender << "!" << endl;
    cout << defender << " is attacked!." << endl;
}

void ConflictManager::betrayAlliance(string attacker, string ally)
{
    cout << attacker << " has betrayed their alliance with " << ally << "!" << endl;
    eventhappen = "Broked.";
}

void MapSystem::initializegrid()
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            grid[i][j] = '.';
            kingdoms[i][j] = "";
        }
    }
}
void MapSystem::placeKingdom(string player, int x, int y)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (kingdoms[i][j] == player)
            {
                clearPosition(i, j);
            }
        }
    }

    grid[x][y] = toupper(player[0]);
    kingdoms[x][y] = player;
    cout << player << " placed at (" << x << "," << y << ")" << endl;
}
void MapSystem::clearPosition(int x, int y)
{
    grid[x][y] = '.';
    kingdoms[x][y] = "";

}
void MapSystem::movePlayer(string player, string direction)
{
    int x = -1, y = -1;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (kingdoms[i][j] == player)
            {
                x = i;
                y = j;
                break;
            }
        }
        if (x != -1)
        {
            break;
        }
    }

    if (x == -1)
    {
        cout << player << " not found on map!\n";
        return;
    }

    int newx = x, newy = y;

    if (direction == "up")
    {
        newx--;
    }
    else if (direction == "down")
    {
        newx++;
    }
    else if (direction == "left")
    {
        newy--;
    }
    else if (direction == "right")
    {
        newy++;
    }
    else
    {
        cout << "Invalid direction! Use: up, down, left, right" << endl;
        return;
    }
    grid[x][y] = '.';
    kingdoms[x][y] = "";

    grid[newx][newy] = player[0];
    kingdoms[newx][newy] = player;
    cout << player << " moved to (" << newx << "," << newy << ")" << endl;
    displayMap();
}

void MapSystem::displayMap()
{
    cout << "Current Game Map : " << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (kingdoms[i][j] != "")
            {

                cout << "[ " << grid[i][j] << " ]";
            }
            else
            {
                cout << "[   ]";
            }
        }
        cout << endl;
    }
    cout << "Kingdom Positions : " << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (kingdoms[i][j] != "")
            {
                cout << kingdoms[i][j] << " at (" << i << "," << j << ")" << endl;
            }
        }
    }
}
void Logger::logEvent(string type, string data)
{
    cout << "[" << type << "] " << data << endl;
}

// Population  
Population::Population()
{
    totalPopulation = 1000;
    growthRate = 0.02;
    healthStatus = 80.0;
    revoltRisk = 10.0;
    employment = 70.0;
}
Population::~Population()
{

}
void Population::validateInputs()
{
    if (totalPopulation < 0 || healthStatus < 0 || revoltRisk < 0 || employment < 0 || employment > 100)
    {
        cout << "Negative or invalid population values" << endl;
    }
}
void Population::updatePopulation(double foodSupply, double employment, double shelter)
{
    if (foodSupply < 0 || employment < 0 || shelter < 0)
    {
        cout << "Negative supply values are invalid" << endl;
        return;
    }
    growthRate = (foodSupply * 0.01 + employment * 0.005 + shelter * 0.005) - 0.01;
    totalPopulation += (int)(totalPopulation * growthRate);
    healthStatus = healthStatus + foodSupply * 0.1 + shelter * 0.05 - 5.0;
    if (healthStatus > 100.0)
    {
        healthStatus = 100.0;
    }
    revoltRisk = revoltRisk + (100.0 - healthStatus) * 0.02 + (100.0 - employment) * 0.03;
    if (revoltRisk > 100.0)
    {
        revoltRisk = 100.0;
    }
    validateInputs();
}
void Population::triggerDisease(double severity)
{
    if (severity < 0 || severity > 100)
    {
        cout << "Invalid disease severity" << endl;
        return;
    }
    healthStatus = healthStatus - severity;
    if (healthStatus < 0.0)
    {
        healthStatus = 0.0;
    }
    totalPopulation -= (int)(totalPopulation * (severity / 200.0));
    revoltRisk = revoltRisk + severity * 0.1;
    if (revoltRisk > 100.0)
    {
        revoltRisk = 100.0;
    }
    validateInputs();
}
int Population::checkRevolt()
{
    if (revoltRisk > 80.0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
int Population::getTotalPopulation() const
{
    return totalPopulation;
}
double Population::getRevoltRisk() const
{
    return revoltRisk;
}
void Population::saveState(ofstream& outFile) const
{
    if (!outFile)
    {
        cout << "Failed to write to save file" << endl;
    }
    else
    {
        outFile << totalPopulation << " " << growthRate << " " << healthStatus << " " << revoltRisk << " " << employment << endl;
    }
}
void Population::loadState(ifstream& inFile)
{
    if (!inFile)
    {
        cout << "Failed to read from save file" << endl;
    }
    else
    {
        inFile >> totalPopulation >> growthRate >> healthStatus >> revoltRisk >> employment;
        if (inFile.fail())
        {
            cout << "Failed to parse save file" << endl;
        }
        validateInputs();
    }
}
void Population::setEmployment(double employment)
{
    if (employment < 0 || employment > 100)
    {
        cout << "Invalid employment" << endl;
        return;
    }
    this->employment = employment;
    revoltRisk += (100.0 - employment) * 0.03;
    if (revoltRisk > 100.0)
    {
        revoltRisk = 100.0;
    }
    validateInputs();
}
double Population::getEmployment() const
{
    return employment;
}
void Population::reducePopulation(int number)
{
    if (number < 0 || number > totalPopulation)
    {
        cout << "Invalid population reduction" << endl;
        return;
    }
    totalPopulation -= number;
    validateInputs();
}

//  Resources

Resources::Resources() : resourceCount(4)
{
    resourceQuantities = new int[resourceCount];
    for (int i = 0; i < resourceCount; i++)
    {
        resourceQuantities[i] = 100;
    }
}
Resources::~Resources()
{
    delete[] resourceQuantities;
}
void Resources::validateInputs()
{
    for (int i = 0; i < resourceCount; i++)
    {
        if (resourceQuantities[i] < 0)
        {
            cout << "Negative resource quantities" << endl;
        }
    }
}
void Resources::gatherResources(int food, int wood, int stone, int iron)
{
    if (food < 0 || wood < 0 || stone < 0 || iron < 0)
    {
        cout << "Negative resource amounts are invalid" << endl;
        return;
    }
    resourceQuantities[0] += food;
    resourceQuantities[1] += wood;
    resourceQuantities[2] += stone;
    resourceQuantities[3] += iron;
    validateInputs();
}
void Resources::consumeResources(int food, int wood, int stone, int iron)
{
    if (food < 0 || wood < 0 || stone < 0 || iron < 0 || food > resourceQuantities[0] || wood > resourceQuantities[1] || stone > resourceQuantities[2] || iron > resourceQuantities[3])
    {
        cout << "Invalid or insufficient resource amounts" << endl;
        return;
    }
    resourceQuantities[0] -= food;
    resourceQuantities[1] -= wood;
    resourceQuantities[2] -= stone;
    resourceQuantities[3] -= iron;
    validateInputs();
}
void Resources::tradeResources(int giveType, int giveAmount, int receiveType, int receiveAmount)
{
    if (giveType < 0 || giveType >= resourceCount || receiveType < 0 || receiveType >= resourceCount || giveAmount < 0 || receiveAmount < 0 || giveAmount > resourceQuantities[giveType])
    {
        cout << "Invalid trade parameters" << endl;
        return;
    }
    resourceQuantities[giveType] -= giveAmount;
    resourceQuantities[receiveType] += receiveAmount;
    validateInputs();
}
int Resources::getResource(int type) const
{
    if (type < 0 || type >= resourceCount)
    {
        cout << "Invalid resource type" << endl;
        return 0;
    }
    return resourceQuantities[type];
}
void Resources::saveState(ofstream& outFile) const
{
    if (!outFile)
    {
        cout << "Failed to write to save file" << endl;
    }
    else
    {
        outFile << resourceCount;

        for (int i = 0; i < resourceCount; i++)
        {
            outFile << " " << resourceQuantities[i];
        }
        outFile << endl;
    }
}
void Resources::loadState(ifstream& inFile)
{
    if (!inFile)
    {
        cout << "Failed to read from save file" << endl;
    }
    else
    {
        inFile >> resourceCount;
        delete[] resourceQuantities;
        resourceQuantities = new int[resourceCount];
        for (int i = 0; i < resourceCount; i++)
        {
            inFile >> resourceQuantities[i];
        }
        if (inFile.fail())
        {
            cout << "Failed to parse save file" << endl;
        }
        validateInputs();
    }
}

// Social Structure

SocialStructure::SocialStructure()
{
    morale = 50.0;
    education = 50.0;
}
SocialStructure::~SocialStructure()
{

}
void SocialStructure::validateInputs()
{
    if (morale < 0 || education < 0)
    {
        cout << "Negative social values" << endl;
    }
}
void SocialStructure::improveMorale(double amount, Population& population, Economy& economy)
{
    if (amount < 0)
    {
        cout << "Invalid morale amount" << endl;
        return;
    }
    morale += amount;
    if (morale > 100.0)
    {
        morale = 100.0;
    }
    population.setEmployment(population.getEmployment() + amount * 0.1);
    economy.generateIncome((int)(amount * 10.0));
    validateInputs();
}
void SocialStructure::improveEducation(double amount, Population& population, Economy& economy)
{
    if (amount < 0)
    {
        cout << "Invalid education amount" << endl;
        return;
    }
    education += amount;
    if (education > 100.0)
    {
        education = 100.0;
    }
    population.setEmployment(population.getEmployment() + amount * 0.05);
    economy.generateIncome((int)(amount * 5.0));
    validateInputs();
}
double SocialStructure::getMorale() const
{
    return morale;
}
double SocialStructure::getEducation() const
{
    return education;
}
void SocialStructure::saveState(ofstream& outFile) const
{
    if (!outFile)
    {
        cout << "Failed to write to save file" << endl;
    }
    else
    {
        outFile << morale << " " << education << endl;
    }
}
void SocialStructure::loadState(ifstream& inFile)
{
    if (!inFile)
    {
        cout << "Failed to read from save file" << endl;
    }
    else
    {
        inFile >> morale >> education;
        if (inFile.fail())
        {
            cout << "Failed to parse save file" << endl;
        }
        validateInputs();
    }
}

//   Leadership

Leadership::Leadership()
{
    influence = 50.0;
    taxRate = 20.0;
}
Leadership::~Leadership()
{

}

void Leadership::validateInputs()
{
    if (influence < 0 || taxRate < 0 || taxRate > 100)
    {
        cout << "Invalid leadership values" << endl;
    }
}
void Leadership::setTaxRate(double rate, Economy& economy, Population& population)
{
    if (rate < 0 || rate > 100)
    {
        cout << "Invalid tax rate" << endl;
        return;
    }
    taxRate = rate;
    economy.generateIncome((int)(rate * 10.0));
    population.setEmployment(population.getEmployment() - rate * 0.1);
    validateInputs();
}
void Leadership::boostInfluence(double amount, Economy& economy)
{
    if (amount < 0)
    {
        cout << "Invalid influence amount" << endl;
        return;
    }
    influence += amount;
    if (influence > 100.0)
    {
        influence = 100.0;
    }
    economy.generateIncome((int)(amount * 5.0));
    validateInputs();
}
void Leadership::implementWelfare(Population& population, Economy& economy)
{
    population.setEmployment(population.getEmployment() + 5.0);
    economy.generateIncome(-100);
    influence += 10.0;
    if (influence > 100.0)
    {
        influence = 100.0;
    }
    validateInputs();
}
double Leadership::getInfluence() const
{
    return influence;
}
double Leadership::getTaxRate() const
{
    return taxRate;
}
void Leadership::saveState(ofstream& outFile) const
{
    if (!outFile)
    {
        cout << "Failed to write to save file" << endl;
    }
    else
    {
        outFile << influence << " " << taxRate << endl;
    }
}
void Leadership::loadState(ifstream& inFile)
{
    if (!inFile)
    {
        cout << "Failed to read from save file" << endl;
    }
    else
    {
        inFile >> influence >> taxRate;
        if (inFile.fail())
        {
            cout << "Failed to parse save file" << endl;
        }
        validateInputs();
    }
}