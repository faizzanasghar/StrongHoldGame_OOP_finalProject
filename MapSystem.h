#pragma once
#include <string>

class MapSystem {
public:
    char grid[5][5];
    std::string kingdoms[5][5];
    void initializegrid();
    void clearPosition(int x, int y);
    void placeKingdom(const std::string& player, int x, int y);
    void movePlayer(const std::string& player, const std::string& direction);
    void displayMap();
};
