/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Comp.h
 * Author: hanne
 *
 * Created on April 14, 2024, 1:24 PM
 */

#ifndef COMP_H
#define COMP_H

#include "Player.h"

struct Point {
    int x, y;
};

class Comp : public Player {
private:
    bool smart;
    Point lastHit;
    bool hasLastHit = false;

    void linsearch(char board[BOARD_SIZE][BOARD_SIZE], int& row, int& col);
    void cardinalSearch(char board[BOARD_SIZE][BOARD_SIZE], int& row, int& col);

public:
    const static PlayerType TYPE = PlayerType::COMP;

    Comp();
    Comp(bool smart);

    // These functions are virtual so that they can be overridden in the derived class
    void generateMove(int&, int&);
    void promptShipPlacement(char board[10][10]);
    void attackCell(int, int, Player*);
    void smartAI(int row, int col, Player* opponent);
    void dumbAI(int row, int col, Player* opponent);

    // 
    void serialize(stringstream&, int&) override;
    void deserialize(fstream&) override;
};

#endif /* COMP_H */

