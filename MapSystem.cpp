#include "MapSystem.h"
#include <iostream>

void MapSystem::initializegrid() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            grid[i][j] = '.';
            kingdoms[i][j] = "";
        }
    }
}

void MapSystem::placeKingdom(const std::string& player, int x, int y) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (kingdoms[i][j] == player) {
                clearPosition(i, j);
            }
        }
    }

    grid[x][y] = toupper(player[0]);
    kingdoms[x][y] = player;
    std::cout << player << " placed at (" << x << "," << y << ")" << std::endl;
}

void MapSystem::clearPosition(int x, int y) {
    grid[x][y] = '.';
    kingdoms[x][y] = "";
}

void MapSystem::movePlayer(const std::string& player, const std::string& direction) {
    int x = -1, y = -1;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (kingdoms[i][j] == player) {
                x = i;
                y = j;
                break;
            }
        }
        if (x != -1) {
            break;
        }
    }

    if (x == -1) {
        std::cout << player << " not found on map!\n";
        return;
    }

    int newx = x, newy = y;

    if (direction == "up") {
        newx--;
    } else if (direction == "down") {
        newx++;
    } else if (direction == "left") {
        newy--;
    } else if (direction == "right") {
        newy++;
    } else {
        std::cout << "Invalid direction! Use: up, down, left, right" << std::endl;
        return;
    }
    // bounds checking
    if (newx < 0 || newx >= 5 || newy < 0 || newy >= 5) {
        std::cout << "Move would go out of bounds; action cancelled." << std::endl;
        return;
    }

    grid[x][y] = '.';
    kingdoms[x][y] = "";

    grid[newx][newy] = player[0];
    kingdoms[newx][newy] = player;
    std::cout << player << " moved to (" << newx << "," << newy << ")" << std::endl;
    displayMap();
}

void MapSystem::displayMap() {
    std::cout << "Current Game Map : " << std::endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (kingdoms[i][j] != "") {
                std::cout << "[ " << grid[i][j] << " ]";
            } else {
                std::cout << "[   ]";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Kingdom Positions : " << std::endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (kingdoms[i][j] != "") {
                std::cout << kingdoms[i][j] << " at (" << i << "," << j << ")" << std::endl;
            }
        }
    }
}
