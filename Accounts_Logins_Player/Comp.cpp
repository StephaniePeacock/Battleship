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

void Comp::placeShips() {
    // Define ship types and their lengths

    for (const auto& ship : SHIP_SIZES) {
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

bool Comp::shoot(Player* opponent) {
    int row = 0, col = 0;
    if (smart) {
        if (!inCardinalSearch) {
            smartAI(row, col, opponent);
            if (inCardinalSearch) return false;
        }
        if (inCardinalSearch) {
            cardinalSearch(row, col, opponent);
        }
    }
    else {
        dumbAI(row, col, opponent);
    }
    return false;
}

void Comp::smartAI(int& row, int& col, Player* opponent) {
    linSearch(row, col, opponent);
}

void Comp::linSearch(int& row, int& col, Player* opponent) {
    srand(time(NULL));
    bool found = false;
    while (!found) {
        row = rand() % 10;
        col = rand() % 10;

        if (opponent->getBoard(row, col) != HIT_CELL && opponent->getBoard(row, col) != MISS_CELL) {
            found = true;
            std::cout << "Valid cell found at: (" << char('A' + row) << ", " << col + 1 << "). Executing attack..." << std::endl;
            attackPosition(row, col, opponent);
        }
    }
}

void Comp::cardinalSearch(int& row, int& col, Player* opponent) {
    static int direction = 0;
    int dRow[] = {0, 1, 0, -1}; // Right, Down, Left, Up
    int dCol[] = {1, 0, -1, 0};

    int checkRow = row + dRow[direction];
    int checkCol = col + dCol[direction];

    if (checkRow >= 0 && checkRow < 10 && checkCol >= 0 && checkCol < 10) {
        if (opponent->getBoard(checkRow, checkCol) != HIT_CELL && opponent->getBoard(checkRow, checkCol) != MISS_CELL) {
            std::cout << "Checking valid cell at (" << char('A' + checkRow) << ", " << checkCol + 1 << ")" << std::endl;
            attackPosition(checkRow, checkCol, opponent);
            if (opponent->getBoard(checkRow, checkCol) == MISS_CELL) {
                direction = (direction + 1) % 4;
            }
        } else {
            direction = (direction + 1) % 4; 
        }
    } else {
        direction = (direction + 1) % 4; 
    }

    if (direction == 0) {
        std::cout << "Completed full rotation for cardinal search. Reverting to linear search." << std::endl;
        row = checkRow;
        col = checkCol;
    }
}

bool Comp::isValid(int& row, int& col, Player* opponent) {
    return row >= 0 && row < 10 && col >= 0 && col < 10 &&
           opponent->getBoard(row, col) != HIT_CELL &&
           opponent->getBoard(row, col) != MISS_CELL;
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
     * bool: isInCardinalSearch in cardinal search or not (smart AI attribute)
     */
    
    //// Serialize base class (Player) data
    
    Player::serialize(buffer, size);
    
    //// Serialize additional instance members unique to Comp
    
    // Store smart boolean value
    buffer.write(reinterpret_cast<char*>(&smart), sizeof(smart));
    size += sizeof(smart);
    
    buffer.write(reinterpret_cast<char*>(&inCardinalSearch), sizeof(inCardinalSearch));
    size += sizeof(inCardinalSearch);
}

void Comp::deserialize(fstream& file) {
    
    //// Deserialize base class (Player) data
    
    Player::deserialize(file);
    
    //// Deserialize additional instance members unique to Comp
    
    // Read smart boolean value
    file.read(reinterpret_cast<char*>(&smart), sizeof(smart));
    
    file.read(reinterpret_cast<char*>(&inCardinalSearch), sizeof(inCardinalSearch));
}