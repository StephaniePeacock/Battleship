/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/*
 * File:   Player.h
 * Author: hanne
 *
 * Created on April 14, 2024, 11:15 AM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <random>
#include <unordered_map>

// A flag to aid in reconstructing Player objects from binary
enum class PlayerType : short unsigned int
{
    PLAYER,
    COMP
};

using namespace std;

class Player
{

private:
    char board[BOARD_SIZE][BOARD_SIZE];         // Copied over to Comp
    char shots[BOARD_SIZE][BOARD_SIZE];         // Copied over to Comp
    unordered_map<char, int> shipCounts;        // Copied over to Comp
    int unsunk;
    // mutators
    //    void setUnsunk();





    
protected:
    
    
public:
    const static PlayerType TYPE = PlayerType::PLAYER;
    Player();            // constructor
    ~Player();           // destructor
    void promptShipPlacement();
    bool isValidPlacement(int, int, int, char);
    bool isValidCoordinate(int row, int col)
    {
        return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
    }
    bool isCellAlreadyHit(int row, int col)
    {
        return (board[row][col] == HIT_CELL || board[row][col] == MISS_CELL);
    }
    virtual void attackCell(int, int, Player *);        // Set this to virtual so that it can be overridden in the derived class
    
    bool placeShip(int, int, int, char, char);

    int getUnsunk() { return this->unsunk; }
    void setBoard(int, int, const char);
    void setShots(int, int, const char);    
    char getBoard(int, int);
    void getBoardArray(char [BOARD_SIZE][BOARD_SIZE]);
    char getShots(int, int);
    void getShotsArray(char [BOARD_SIZE][BOARD_SIZE]);
    void displayBoard(); // print current board
    void displayShots();
    static int convToInt(string);
    virtual void serialize(stringstream &, int &);
    virtual void deserialize(fstream &);
};

#endif /* PLAYER_H */
