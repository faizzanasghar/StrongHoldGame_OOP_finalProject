#include"Header.h"
#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>

using namespace std;
class Game
{
private:
    SocialStructure* socialStructure;
    Population* population;
    Military* military;
    Leadership* leadership;
    Economy* economy;
    Bank* bank;
    Resources* resources;
    EventHandler* eventHandler;
    AllianceManager* allianceManager;
    TradeSystem* tradeSystem;
    ConflictManager* conflictManager;
    MapSystem* mapSystem;
    Logger* logger;
    comms* communication;
    int isRunning;
    int turn;

    void saveGame()
    {
        ofstream outFile("game.txt");
        if (!outFile)
        {
            cout << "Failed to open game_save.txt" << endl;
        }
        else
        {
            population->saveState(outFile);
            resources->saveState(outFile);
            military->saveState(outFile);
            economy->saveState(outFile);
            leadership->saveState(outFile);
            bank->saveState(outFile);
            eventHandler->saveState(outFile);
            socialStructure->saveState(outFile);
            outFile << turn << endl;
            outFile.close();
        }
    }

    void loadGame()
    {
        ifstream inFile("game.txt");
        if (!inFile)
        {
            cout << "Failed to open game_save.txt" << endl;
        }
        else
        {
            population->loadState(inFile);
            resources->loadState(inFile);
            military->loadState(inFile);
            economy->loadState(inFile);
            leadership->loadState(inFile);
            bank->loadState(inFile);
            eventHandler->loadState(inFile);
            socialStructure->loadState(inFile);
            inFile >> turn;
            if (inFile.fail())
            {
                cout << "Failed to parse save file" << endl;
            }
            inFile.close();
        }
    }

    void logScore()
    {
        ofstream logFile("score.txt", ios::app);
        if (!logFile)
        {
            cout << "Failed to open score.txt" << endl;
        }
        else
        {
            logFile << "Turn: " << turn
                << ", Population: " << population->getTotalPopulation()
                << ", Food: " << resources->getResource(0)
                << ", Soldiers: " << military->getSoldierCount()
                << ", Wealth: " << economy->getWealth()
                << ", Influence: " << leadership->getInfluence()
                << ", Reserves: " << bank->getReserves()
                << ", Last Event: " << eventHandler->getLastEventType()
                << ", Morale: " << socialStructure->getMorale()
                << ", Education: " << socialStructure->getEducation() << endl;
            logFile.close();
        }
    }

    void processTurn()
    {
        double food = (double)resources->getResource(0) / 10.0;
        population->updatePopulation(food, population->getEmployment(), 60.0);
        economy->generateIncome(population->getTotalPopulation());
        if (turn % 3 == 0)
        {
            int eventType = turn % 4;
            eventHandler->triggerEvent(eventType, *population, *resources, *military, *economy, *leadership, *bank);
            cout << "Event triggered (type " << eventType << ")!" << endl;
        }
        if (population->checkRevolt())
        {
            cout << "Revolt occurred! Game over!" << endl;
            isRunning = 0;
        }
        logScore();
    }

public:
    Game() : isRunning(0), turn(0)
    {
        socialStructure = new SocialStructure();
        population = new Population();
        military = new Military();
        leadership = new Leadership();
        economy = new Economy();
        bank = new Bank();
        resources = new Resources();
        eventHandler = new EventHandler();
        allianceManager = new AllianceManager();
        tradeSystem = new TradeSystem();
        conflictManager = new ConflictManager();
        mapSystem = new MapSystem();
        logger = new Logger();
        communication = new comms();
    }

    ~Game()
    {
        delete socialStructure;
        delete population;
        delete military;
        delete leadership;
        delete economy;
        delete bank;
        delete resources;
        delete eventHandler;
        delete allianceManager;
        delete tradeSystem;
        delete conflictManager;
        delete mapSystem;
        delete logger;
        delete communication;
    }
    void setColor(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void run()
    {
        isRunning = 1;
        logScore();
        while (isRunning)
        {
            setColor(20);
            cout << "\t\t\t\t\t\t\t\t";
            cout << "===================================================================\n";
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(20);
            cout << "|                          STRONG HOLD GAME                       |\n";
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(20);
            cout << "===================================================================\n";
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(279);
            cout << "|                       1. Start Game                             |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(45);
            cout << "|                       2. Load Game                              |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(55);
            cout << "|                       3. Manage Population                      |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(78);
            cout << "|                       4. Manage Resources                       |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(85);
            cout << "|                       5. Manage Military                        |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(95);
            cout << "|                       6. Manage Economy                         |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(105);
            cout << "|                       7. Manage Leadership                      |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(115);
            cout << "|                       8. Manage Bank                            |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(125);
            cout << "|                       9. Manage Social Structure                |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(135);
            cout << "|                       10. Trigger Event                         |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(145);
            cout << "|                       11. Next Turn                             |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(155);
            cout << "|                       12. Communication                         |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(165);
            cout << "|                       13. Alliance Management                   |"; setColor(7);  cout << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(175);
            cout << "|                       14. Trade System                          |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(185);
            cout << "|                       15. Conflict Management                   |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(195);
            cout << "|                       16. Map System                            |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(205);
            cout << "|                       17. Exit                                  |" << endl;
            setColor(7);
            cout << "\t\t\t\t\t\t\t\t";
            setColor(20);
            cout << "===================================================================\n";
            setColor(11);
            cout << "\nEnter choice: ";
            int choice;
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
            case 1:
                setColor(19);
                cout << "\n       *** Starting game ***" << endl;
                turn = 0;
                setColor(7);
                saveGame();
                break;
            case 2:
                setColor(54);
                cout << "        *** Loading game ***" << endl;
                setColor(7);
                loadGame();
                break;
            case 3:
            {
                setColor(45); 
                cout << "\n----------------------------------------------\n";
                cout << "|            1. Update Population             |" << endl;
                cout << "|            2. Trigger Disease               |" << endl;
                cout << "\n----------------------------------------------\n";
                setColor(7);
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                if (subChoice == 1)
                {
                    double food = (double)resources->getResource(0) / 10.0;
                    cout << "Enter employment, shelter (0-100): ";
                    double emp, shelter;
                    cin >> emp >> shelter;
                    cin.ignore();
                    population->updatePopulation(food, emp, shelter);
                    cout << "Population: " << population->getTotalPopulation() << ", Revolt Risk: " << population->getRevoltRisk() << endl;
                }
                else if (subChoice == 2)
                {
                    cout << "Enter disease severity (0-100): ";
                    double severity;
                    cin >> severity;
                    cin.ignore();
                    population->triggerDisease(severity);
                    cout << "Population: " << population->getTotalPopulation() << ", Revolt Risk: " << population->getRevoltRisk() << endl;
                    if (population->checkRevolt())
                    {
                        cout << "Revolt occurred!" << endl;
                    }
                }
                else
                {
                    cout << "Invalid sub-choice" << endl;
                }
                logScore();
                break;
            }
            case 4:
            {
                cout << "1. Gather Resources" << endl;
                cout << "2. Consume Resources" << endl;
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                if (subChoice == 1)
                {
                    cout << "Enter food, wood, stone, iron to gather: ";
                    int food, wood, stone, iron;
                    cin >> food >> wood >> stone >> iron;
                    cin.ignore();
                    resources->gatherResources(food, wood, stone, iron);
                    cout << "Resources: Food=" << resources->getResource(0) << ", Wood=" << resources->getResource(1) << ", Stone=" << resources->getResource(2) << ", Iron=" << resources->getResource(3) << endl;
                }
                else if (subChoice == 2)
                {
                    cout << "Enter food, wood, stone, iron to consume: ";
                    int food, wood, stone, iron;
                    cin >> food >> wood >> stone >> iron;
                    cin.ignore();
                    resources->consumeResources(food, wood, stone, iron);
                    cout << "Resources: Food=" << resources->getResource(0) << ", Wood=" << resources->getResource(1) << ", Stone=" << resources->getResource(2) << ", Iron=" << resources->getResource(3) << endl;
                }
                else
                    cout << "Invalid sub-choice" << endl;
                logScore();
                break;
            }
            case 5:
            {
                cout << "1. Recruit Soldiers" << endl;
                cout << "2. Equip Weapons" << endl;
                cout << "3. Defend Attack" << endl;
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                if (subChoice == 1)
                {
                    cout << "Enter number of soldiers to recruit: ";
                    int soldiers;
                    cin >> soldiers;
                    cin.ignore();
                    military->recruitSoldiers(soldiers, *population);
                    cout << "Soldiers: " << military->getSoldierCount() << ", Strength: " << military->getStrength() << endl;
                }
                else if (subChoice == 2)
                {
                    cout << "Enter iron amount to equip weapons: ";
                    int iron2;
                    cin >> iron2;
                    cin.ignore();
                    military->equipWeapons(iron2, *resources);
                    cout << "Soldiers: " << military->getSoldierCount() << ", Strength: " << military->getStrength() << endl;
                }
                else if (subChoice == 3)
                {
                    cout << "Enter attack strength (0-100): ";
                    double attack;
                    cin >> attack;
                    cin.ignore();
                    military->defendAttack(attack);
                    cout << "Soldiers: " << military->getSoldierCount() << ", Strength: " << military->getStrength() << endl;
                }
                else
                    cout << "Invalid sub-choice" << endl;
                logScore();
                break;
            }
            case 6:
            {
                cout << "1. Generate Income" << endl;
                cout << "2. Trade Resources" << endl;
                cout << "3. Adjust Employment" << endl;
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                if (subChoice == 1)
                {
                    cout << "Generating income..." << endl;
                    economy->generateIncome(population->getTotalPopulation());
                    cout << "Wealth: " << economy->getWealth() << ", Employment Rate: " << economy->getEmploymentRate() << endl;
                }
                else if (subChoice == 2)
                {
                    cout << "Enter give type, give amount, receive type, receive amount: ";
                    int giveType, giveAmount, receiveType, receiveAmount;
                    cin >> giveType >> giveAmount >> receiveType >> receiveAmount;
                    cin.ignore();
                    economy->tradeResources(giveType, giveAmount, receiveType, receiveAmount, *resources);
                    cout << "Wealth: " << economy->getWealth() << ", Resources: Food=" << resources->getResource(0) << ", Wood=" << resources->getResource(1) << ", Stone=" << resources->getResource(2) << ", Iron=" << resources->getResource(3) << endl;
                }
                else if (subChoice == 3)
                {
                    cout << "Enter new employment rate (0-100): ";
                    double rate;
                    cin >> rate;
                    cin.ignore();
                    economy->adjustEmployment(rate, *population);
                    cout << "Wealth: " << economy->getWealth() << ", Employment Rate: " << economy->getEmploymentRate() << endl;
                }
                else
                    cout << "Invalid sub-choice" << endl;
                logScore();
                break;
            }
            case 7:
            {
                cout << "1. Set Tax Rate" << endl;
                cout << "2. Boost Influence" << endl;
                cout << "3. Implement Welfare" << endl;
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                if (subChoice == 1)
                {
                    cout << "Enter new tax rate (0-100): ";
                    double taxRate;
                    cin >> taxRate;
                    cin.ignore();
                    leadership->setTaxRate(taxRate, *economy, *population);
                    cout << "Influence: " << leadership->getInfluence() << ", Tax Rate: " << leadership->getTaxRate() << endl;
                }
                else if (subChoice == 2)
                {
                    cout << "Enter influence boost amount: ";
                    double influenceAmount;
                    cin >> influenceAmount;
                    cin.ignore();
                    leadership->boostInfluence(influenceAmount, *economy);
                    cout << "Influence: " << leadership->getInfluence() << ", Tax Rate: " << leadership->getTaxRate() << endl;
                }
                else if (subChoice == 3)
                {
                    cout << "Implementing welfare..." << endl;
                    leadership->implementWelfare(*population, *economy);
                    cout << "Influence: " << leadership->getInfluence() << ", Tax Rate: " << leadership->getTaxRate() << endl;
                }
                else
                    cout << "Invalid sub-choice" << endl;
                logScore();
                break;
            }
            case 8:
            {
                cout << "1. Take Loan" << endl;
                cout << "2. Make Investment" << endl;
                cout << "3. Repay Loan" << endl;
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                if (subChoice == 1)
                {
                    cout << "Enter loan amount: ";
                    double loan;
                    cin >> loan;
                    cin.ignore();
                    bank->takeLoan(loan, *economy, *population);
                    cout << "Reserves: " << bank->getReserves() << ", Loan Amount: " << bank->getLoanAmount() << endl;
                }
                else if (subChoice == 2)
                {
                    cout << "Enter investment amount: ";
                    double investment;
                    cin >> investment;
                    cin.ignore();
                    bank->makeInvestment(investment, *economy, *population);
                    cout << "Reserves: " << bank->getReserves() << ", Loan Amount: " << bank->getLoanAmount() << endl;
                }
                else if (subChoice == 3)
                {
                    cout << "Enter repayment amount: ";
                    double repayment;
                    cin >> repayment;
                    cin.ignore();
                    bank->repayLoan(repayment, *economy);
                    cout << "Reserves: " << bank->getReserves() << ", Loan Amount: " << bank->getLoanAmount() << endl;
                }
                else
                    cout << "Invalid sub-choice" << endl;
                logScore();
                break;
            }
            case 9:
            {
                cout << "Enter morale amount, education amount: ";
                double moraleAmount, educationAmount;
                cin >> moraleAmount >> educationAmount;
                cin.ignore();
                socialStructure->improveMorale(moraleAmount, *population, *economy);
                socialStructure->improveEducation(educationAmount, *population, *economy);
                cout << "Morale: " << socialStructure->getMorale() << ", Education: " << socialStructure->getEducation() << endl;
                logScore();
                break;
            }
            case 10:
                cout << "Enter event type (0-3): ";
                int eventType;
                cin >> eventType;
                cin.ignore();
                eventHandler->triggerEvent(eventType, *population, *resources, *military, *economy, *leadership, *bank);
                cout << "Last Event: " << eventHandler->getLastEventType() << ", Population: " << population->getTotalPopulation() << ", Wealth: " << economy->getWealth() << endl;
                logScore();
                break;
            case 11:
            {
                cout << "Advancing to next turn..." << endl;
                turn++;
                processTurn();
                cout << "Turn " << turn << " completed." << endl;
                break;
            }
            case 12:
            {
                cout << "1. Send Message" << endl;
                cout << "2. Receive Message" << endl;
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                string from, to, message;
                if (subChoice == 1)
                {
                    cout << "Enter from, to, message: ";
                    getline(cin, from);
                    getline(cin, to);
                    getline(cin, message);
                    communication->sendMessage(from, to, message);
                }
                else if (subChoice == 2)
                {
                    cout << "Enter player: ";
                    getline(cin, from);
                    communication->receiveMessage(from);
                }
                else
                {
                    cout << "Invalid sub-choice" << endl;
                    break;
                }

            }
            case 13:
            {
                cout << "1. Form Alliance" << endl;
                cout << "2. Break Alliance" << endl;
                cout << "3. Check Alliance Status" << endl;
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                string player1, player2;
                cout << "Enter player names: ";
                cin >> player1 >> player2;
                cin.ignore();
                if (subChoice == 1)
                {
                    allianceManager->formAlliance(player1, player2);
                }
                else if (subChoice == 2)
                {
                    allianceManager->breakAlliance(player1, player2);
                }
                else if (subChoice == 3)
                {
                    allianceManager->getAllianceStatus(player1, player2);
                }
                else
                {
                    cout << "Invalid sub-choice" << endl;
                    break;
                }
            }
            case 14:
            {
                cout << "1. Offer Trade" << endl;
                cout << "2. Attempt Smuggle" << endl;
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                string from, to, resource;
                int quantity;
                if (subChoice == 1)
                {
                    cout << "Enter from, to, resource, quantity: ";
                    cin >> from >> to >> resource >> quantity;
                    cin.ignore();
                    tradeSystem->offerTrade(from, to, resource, quantity);
                }
                else if (subChoice == 2)
                {
                    cout << "Enter from, to, resource: ";
                    cin >> from >> to >> resource;
                    cin.ignore();
                    tradeSystem->attemptSmuggle(from, to, resource);
                }
                else
                {
                    cout << "Invalid sub-choice" << endl;
                    break;
                }
            }
            case 15:
            {
                cout << "1. Declare War" << endl;
                cout << "2. Betray Alliance" << endl;
                cout << "Enter sub-choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                string attacker, defender;
                if (subChoice == 1)
                {
                    cout << "Enter attacker, defender: ";
                    cin >> attacker >> defender;
                    cin.ignore();
                    conflictManager->declareWar(attacker, defender);
                }
                else if (subChoice == 2)
                {
                    cout << "Enter attacker, ally: ";
                    cin >> attacker >> defender;
                    cin.ignore();
                    conflictManager->betrayAlliance(attacker, defender);
                }
                else
                {
                    cout << "Invalid sub-choice" << endl;
                    break;
                }
            }
            case 16:
            {
                cout << "1. Place Kingdom" << endl;
                cout << "2. Move Player" << endl;
                cout << "3. Display Map" << endl;
                cout << "Enter choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();
                string player;
                if (subChoice == 1)
                {
                    int x, y;
                    cout << "Enter player, x, y: ";
                    cin >> player >> x >> y;
                    cin.ignore();
                    mapSystem->placeKingdom(player, x, y);
                }
                else if (subChoice == 2)
                {
                    string direction;
                    cout << "Enter player, direction: ";
                    cin >> player >> direction;
                    cin.ignore();
                    mapSystem->movePlayer(player, direction);
                }
                else if (subChoice == 3)
                {
                    mapSystem->displayMap();
                }
                else
                    cout << "Invalid sub-choice" << endl;
                break;
            }
            case 17:
            {
                cout << "Exiting game..." << endl;
                isRunning = 0;
                break;
            }
            default:
            {
                cout << "Invalid choice" << endl;
            }
            }
        }
    }
};

int main()
{

    Game game;
    game.run();
    system("pause");
}