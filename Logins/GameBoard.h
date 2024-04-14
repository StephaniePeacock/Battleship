/* 
 * File:   GameBoard.h
 * Author: Stephanie Peacock
 * Created on April 13, 2024, 12:15 PM
 * Purpose: GameBard Class Specification
 */

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <unordered_map>

using namespace std;

const int BOARD_SIZE = 10;
const char EMPTY_CELL = '-';
const char SHIP_CELL = 'S';
const char HIT_CELL = 'X';
const char MISS_CELL = 'O';

class GameBoard {
private:
    char board[BOARD_SIZE][BOARD_SIZE];
    char shots[BOARD_SIZE][BOARD_SIZE];
    unordered_map<char, int> shipCounts;
    int unsunk;
    //mutators
    void setUnsunk();
    void setBoard(int,int,const char);
    void setShots(int,int,const char);
    //other functions
    bool isValidCoordinate(int row, int col) {
        return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
    }
    bool isValidPlacement(int, int, int, char);
    bool placeShip(int, int, int, char, char);
    
    bool isCellAlreadyHit(int row, int col) {
        return (board[row][col] == HIT_CELL || board[row][col] == MISS_CELL);
    }
    
    
public:
    GameBoard();            //constructor
    ~GameBoard();           //destructor
    void displayBoard();    //print current board
    void displayShots();
    void promptShipPlacement();
    void attackCell(int, int, GameBoard);
    
    int getUnsunk() { return this->unsunk; }
    char getBoard(int,int);
    char getShots(int,int);
};    

#endif /* GAMEBOARD_H */

