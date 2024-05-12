/* 
 * File:   Comp.cpp
 * Author: hannes, Matthew, Leoncio, Marco
 * 
 * Created on April 14, 2024, 1:24 PM
 */

#include "Comp.h"
#include <vector>
#include <ctime>
#include <cstdlib>

Comp::Comp() : Player() {
    this->smart = false;
    this->state = 0;
    this->guesses = 10;
    this->quadrant = 0;
    this->score = 0;
}
Comp::Comp(bool smart) : Player() {
    this->smart = smart;
}

void Comp::promptShipPlacement() {
    // Define ship types and their lengths

    std::vector<pair<char, int>> ships = {{'C', 5}, {'B', 4}, {'S', 3}, {'D', 3}, {'P', 2}};

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
    setUnsunk(5);
    cout << "Computer player has placed its ships." << endl;
}

void Comp::attackCell(int row, int col, Player* opponent) {
    if (smart) {
        //smartAI(row, col, opponent);
        std::cout << "Smart AI not implemented yet." << std::endl;
        // Define row and col based on smart move
    }
    else {
        std::cout << "Dumb AI choosing move..." << std::endl;
        dumbAI(row, col, opponent);
        std::cout << "Dumb AI chose move: Row: " << row << ". Column: " << col << std::endl;
        // Define row and col based on dumb move
    }

    // // By this point, row and col should have been defined by generateMove
    // if (opponent->getBoard(row, col) == SHIP_CELL) {
    //     cout << "Hit!" << endl;
    //     opponent->setBoard(row, col, HIT_CELL);     //
    //     setShots(row, col, HIT_CELL);               // This is for computer's own tracking (Basically the top screen for tracking)
    // }
    // else {
    //     cout << "Miss!" << endl;
    //     opponent->setBoard(row, col, MISS_CELL);
    //     setShots(row, col, MISS_CELL);              // This is for computer's own tracking
    // }
}

void Comp::dumbAI(int& row, int& col, Player* opponent) {
    bool shot = false;
    srand(time(0));

    char shipType;

    if (!state) { 
        while (!shot) {
            int i = rand() % 10;
            int j = rand() % 10; 
            char cell = opponent->getBoard(i, j);
            
            if (cell != HIT_CELL && cell != MISS_CELL) {
                if (cell == EMPTY_CELL) {
                    opponent->setBoard(i, j, MISS_CELL);
                    setShots(i, j, MISS_CELL);
                } else {
                    shipType = cell;
                    quadrant = quadrantDetector(10, 10, j, i);
                    state = 1; 
                    decrementShipHealth(shipType);
                    if (getShipHealth(shipType) == 0) {
                        cout << shipType << " has been sunk!" << endl;
                        int unsunk = getUnsunk();
                        setUnsunk(unsunk - 1);
                    }
                    opponent->setBoard(i, j, HIT_CELL);
                    setShots(i, j, HIT_CELL);
                    score++;
                }
                row = i;
                col = j;
                shot = true;
            }
        }
    } else {
        if (guesses <= 0) {
            guesses = 10;
        }

        int i, j;
        bool status = getRandomPointInQuadrant(quadrant, 10, 10, j, i);
        bool hitFlag = false;
        if (status) {
            char cell = opponent->getBoard(i, j);
            if (cell == EMPTY_CELL) {
                opponent->setBoard(i, j, MISS_CELL);
                setShots(i, j, MISS_CELL);
                cout << "\nMissed!\n";
            } else {
                shipType = cell; 
                decrementShipHealth(shipType);
                if (getShipHealth(shipType) == 0) {
                    cout << shipType << " has been sunk!" << endl;
                    int unsunk = getUnsunk();
                    setUnsunk(unsunk - 1);
                }
                opponent->setBoard(i, j, HIT_CELL);
                setShots(i, j, HIT_CELL);
                score++;
                hitFlag = true;
                cout << "\nHit!\n";
            }
            row = i;
            col = j;
        } else {
            cout << "No more moves in quadrant!";
            hitFlag = true;
            state = 0;
            dumbAI(row, col, opponent);
        }

        if (hitFlag) {
            guesses++;
            state = 1;
        } else {
            guesses--;
            if (guesses <= 0) {
                state = 0;
            }
        }
    }
}

int Comp::quadrantDetector(int width, int height, int x, int y){
    int quadrant = 1;
    if (x >= width/2 && y < height/2) {         // Quadrant 1 (Top right)
        quadrant = 1;
    }
    else if (x < width/2 && y < height/2) {     // Quadrant 2 (Top left)
        quadrant = 2;
    }
    else if (x < width/2 && y >= height/2) {    // Quadrant 3 (Bottom left)
        quadrant = 3;
    }
    else if (x >= width/2 && y >= height/2) {   // Quadrant 4 (Bottom right)
        quadrant = 4;
    }
    return quadrant;
}

bool Comp::movesAvailable(int quadrant) {
    int ti, tj;
    int iLim, jLim;         // Limits for for loops
    if (quadrant == 1) {
        ti = 0;
        tj = 10/2;
        iLim = 10/2;
        jLim = 10;
    }
    else if (quadrant == 2) {
        ti = 0;
        tj = 0;
        iLim = 10/2;
        jLim = 10/2;
    }
    else if (quadrant == 3) {
        ti = 10/2;
        tj = 0;
        iLim = 10;
        jLim = 10/2;
    }
    else {
        ti = 10/2;
        tj = 10/2;
        iLim = 10;
        jLim = 10;
    }

    for (int i = ti; i < iLim; i++) {
        for (int j = tj; j < jLim; j++) {
            char cell = getShots(i, j);
            if (cell != 'X' && cell != 'O') {
                return true;
            }
        }
    }

    return false;
}

bool Comp::getRandomPointInQuadrant(int quadrant, int width, int height, int &x, int &y) {
    srand(time(NULL));
    int i, j;
    if (quadrant == 1) {
        i = 0;
        j = 10/2;
    }
    else if (quadrant == 2) {
        i = 0;
        j = 0;
    }
    else if (quadrant == 3) {
        i = 10/2;
        j = 0;
    }
    else if (quadrant == 4) {
        i = 10/2;
        j = 10/2;
    }
    int tempX, tempY;
    if (movesAvailable(quadrant)) {
        char square;

        do {
            tempX = j + rand() % (10/2);    // Reversed x & y because [i][j] has j as x coordinate (horizontal)
            tempY = i + rand() % (10/2);
            square = getShots(tempY, tempX);
        } while (square == 'X' || square == 'O');   // Keep changing while x or o

        x = tempX;
        y = tempY;

        return true;    // Successful
    }
    else {
        return false;   // No more moves in quadrant
    }
}

bool Comp::isGameOver() {
        if (score == 17) {
            return true;
        }
        else {
            return false;
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