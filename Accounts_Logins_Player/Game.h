/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Game.h
 * Author: hanne
 *
 * Created on April 14, 2024, 1:44 PM
 */

#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
    
private:
    Player* p1;  // Polymorphic: Can be Player or Comp
    Player* p2;  // Polymorphic: Can be Player or Comp
    bool turn;
    
    // Methods
    void doTurn();
    
public:
    Game(Player* p1, Player* p2);
};


#endif /* GAME_H */

