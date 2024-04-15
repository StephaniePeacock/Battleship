/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Player.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 11:15 AM
 */

#include "Player.h"

Player::Player() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board[i][j] = EMPTY_CELL;
                shots[i][j] = EMPTY_CELL;
            }
        }
        shipCounts['C'] = 1; // Carrier
        shipCounts['B'] = 2; // Battleship
        shipCounts['D'] = 3; // Destroyer
        shipCounts['S'] = 3; // Submarine
        shipCounts['P'] = 4; // Patrol Boat
        unsunk = 0;
}

Player::~Player() {
}

void Player::setBoard(int row,int col, const char c){
    board[row][col] = c;
}

void Player::setShots(int row,int col, const char c){
    shots[row][col] = c;
}



// Function to display the current state of the board
void Player::displayBoard() {
    cout << "   A B C D E F G H I J" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << "  ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//display shots taken (based on opponent's board)
void Player::displayShots() {
    cout << "   A B C D E F G H I J" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << "  ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << shots[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if a ship can be placed at the given coordinate
bool Player::isValidPlacement(int row, int col, int size, char direction) {
    if (!isValidCoordinate(row, col) || (direction != 'H' && direction != 'V'))
        return false;

    if (direction == 'H') {
        if (col + size - 1 >= BOARD_SIZE)
            return false;
        for (int j = col; j < col + size; ++j) {
            if (board[row][j] == SHIP_CELL)
                return false;
        }
    }
    else { // direction == 'V'
        if (row + size - 1 >= BOARD_SIZE)
            return false;
        for (int i = row; i < row + size; ++i) {
            if (board[i][col] == SHIP_CELL)
                return false;
        }
    }

    return true;
}

// Function to place a ship on the board
bool Player::placeShip(int row, int col, int size, char direction, char shipType) {
    if (shipCounts[shipType] <= 0 || !isValidPlacement(row, col, size, direction)) {
        cout << "Invalid placement!" << endl;
        return false;
    }

    if (direction == 'H') {
        for (int j = col; j < col + size; ++j) {
            setBoard(row,j,SHIP_CELL);
            unsunk++;
        }
    }
    else { // direction == 'V'
        for (int i = row; i < row + size; ++i) {
            setBoard(i,col,SHIP_CELL);
            unsunk++;
        }
    }

    shipCounts[shipType]--;
    displayBoard(); // Display the board after each placement
    return true;
}

// Function to prompt the user to place ships on the board
void Player::promptShipPlacement() {
    char shipTypes[] = { 'C', 'B', 'D', 'S', 'P' };
    for (char shipType : shipTypes) {
        int size = shipType == 'C' ? 5 : shipType == 'B' ? 4 : shipType == 'D' ? 3 : shipType == 'S' ? 3 : 2;
        cout << "Placing " << size << "-unit " << shipType << " ship." << endl;
        while (true) {
            int row, col;
            char letter;
            char direction;
            cout << "Enter starting coordinates." << endl << "Enter row:";
            cin >> row;
            do {
                cout << "Enter Column: ";
                cin >> letter;
            } while(letter < 'A' || letter > 'J');
            cout << "Enter direction (H for horizontal, V for vertical): ";
            cin >> direction;
            col = letter - 65;
            if (placeShip(row, col, size, direction, shipType)) {
                cout << "Ship placed successfully!" << endl;
                break;
            }
            else {
                cout << "Invalid coordinates or ship placement. Try again." << endl;
            }
        }
    }
}

// Function to attack a cell on the opponent's board
void Player::attackCell(int row, int col, Player enemy) {
    if (enemy.board[row][col] == SHIP_CELL) {
        cout << "Hit!" << endl;
        enemy.setBoard(row,col,HIT_CELL);
        setShots(row,col,HIT_CELL);
    }
    else {
        cout << "Miss!" << endl;
        enemy.setBoard(row,col,MISS_CELL);
        setShots(row,col,MISS_CELL);
    }
}
