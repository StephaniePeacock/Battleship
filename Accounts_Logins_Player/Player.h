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
#include <unordered_map>

#include "Generics.h"

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
    char board[BOARD_SIZE][BOARD_SIZE];
    char shots[BOARD_SIZE][BOARD_SIZE];
    unordered_map<char, int> shipHealth;
    int unsunk;

    // other functions
    bool isValidCoordinate(int row, int col)
    {
        return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
    }
    bool isValidPlacement(int, int, int, char);

    bool isCellAlreadyHit(int row, int col)
    {
        return (board[row][col] == HIT_CELL || board[row][col] == MISS_CELL);
    }

public:
    const static PlayerType TYPE = PlayerType::PLAYER;
    Player();            // constructor
    ~Player();           // destructor
    void displayBoard(); // print current board
    void displayShots();
    void displayShipsHealth();

    // Move these two down from private
    void setBoard(int, int, const char);
    void setShots(int, int, const char);

    // Getters
    char getBoard(int, int);
    char getShots(int, int);

    // These two should be virtual
    virtual void placeShips();
    virtual bool shoot(Player*);
//    virtual void doTurn();
    
    bool placeShip(int, int, int, char, char);
    void attackPosition(int, int, Player*);

    int getUnsunk() { return unsunk; }
    void setUnsunk(int u) { unsunk = u; }       // Added this for the Comp class
    static int convToInt(string);

    // Hashmap functions
    void decrementShipHealth(char);
    int getShipHealth(char);

    virtual void serialize(stringstream &, int &);
    virtual void deserialize(fstream &);
};

#endif /* PLAYER_H */
