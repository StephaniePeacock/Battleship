/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Player.h
 * Author: hanne
 *
 * Created on April 13, 2024, 5:57 PM
 */

#include "Constants.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    bool guesses[BOARDSIZE];
    char ships[BOARDSIZE];
    bool turn;
    int fleet;
public:
    Player(bool guesses[], char ships[], bool turn, int fleet);
};

#endif /* PLAYER_H */

