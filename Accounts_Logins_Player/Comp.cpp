/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Comp.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 1:24 PM
 */

#include "Comp.h"
#include <vector>

Comp::Comp() : Player() {
    this->smart = false;
}
Comp::Comp(bool smart) : Player() {
    this->smart = smart;
}

void Comp::promptShipPlacement() {
    // Define ship types and their lengths

    std::vector<pair<char, int>> ships = {{'A', 5}, {'B', 4}, {'C', 3}, {'D', 3}, {'S', 2}};

    for (const auto& ship : ships) {
        int length = ship.second;
        bool placed = false;

        while (!placed) {
            // Randomly choose orientation (horizontal or vertical)
            bool horizontal = rand() % 2 == 0;
            int x = rand() % 10;
            int y = rand() % 10;

            // Check if the ship can be placed at the randomly chosen position
            if (horizontal && x + length <= 10) {
                placed = true;
                for (int i = x; i < x + length; ++i) {
                    if (this->getBoard(y, i) != '-') {
                        placed = false;
                        break;
                    }
                }
                if (placed) {
                    // Place the ship on the board
                    for (int i = x; i < x + length; ++i) {
                        this->setBoard(y, i, ship.first);
                    }
                }
            } else if (!horizontal && y + length <= 10) {
                placed = true;
                for (int i = y; i < y + length; ++i) {
                    if (this->getBoard(i, x) != '-') {
                        placed = false;
                        break;
                    }
                }
                if (placed) {
                    // Place the ship on the board
                    for (int i = y; i < y + length; ++i) {
                        this->setBoard(i, x, ship.first);
                    }
                }
            }
        }
    }

    cout << "Computer player has placed its ships." << endl;
}

void Comp::attackCell(int row, int col, Player* opponent) {
    if (smart) {
        //smartAI(row, col, opponent);
        std::cout << "Smart AI not implemented yet." << std::endl;
        // Define row and col based on smart move
    }
    else {
        //dumbAI(row, col, opponent);
        std::cout << "Dumb AI not implemented yet." << std::endl;
        // Define row and col based on dumb move
    }

    // By this point, row and col should have been defined by generateMove
    if (opponent->getBoard(row, col) == SHIP_CELL) {
        cout << "Hit!" << endl;
        opponent->setBoard(row, col, HIT_CELL);     //
        setShots(row, col, HIT_CELL);               // This is for computer's own tracking (Basically the top screen for tracking)
    }
    else {
        cout << "Miss!" << endl;
        opponent->setBoard(row, col, MISS_CELL);
        setShots(row, col, MISS_CELL);              // This is for computer's own tracking
    }
}

void Comp::serialize(stringstream& buffer, int& size) {
    /* --Comp serialization binary storage structure--
     * --Everything in Player
     * short unsigned int:  type of object (Player=0, Comp=1)
     * int:                 size of board
     * char[board size]:    char for each item in board array
     * char[board size]:    char for each item in shots array
     * int:                 shipCounts map count
     * char & int pars:     first key (char) then value (int)
     *                        for each pair in map
     * int:                 unsunk integer value
     * --Plus the following unique to Comp
     * bool:                smart or dumb AI
     */
    
    //// Serialize base class (Player) data
    
    Player::serialize(buffer, size);
    
    //// Serialize additional instance members unique to Comp
    
    // Store smart boolean value
    buffer.write(reinterpret_cast<char*>(&smart), sizeof(smart));
    size += sizeof(smart);
}

void Comp::deserialize(fstream& file) {
    
    //// Deserialize base class (Player) data
    
    Player::deserialize(file);
    
    //// Deserialize additional instance members unique to Comp
    
    // Read smart boolean value
    file.read(reinterpret_cast<char*>(&smart), sizeof(smart));
}