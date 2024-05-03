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

#include "Generics.h"
#include "Player.h"
#include "Comp.h"

namespace game {
    const int MAXUID = 102;  // MAXSTR + 1 (for "_") + 20 (largest 64-bit int is 20 chars wide)
}

class Game {

private:
    char uid[game::MAXUID];
    Player *p1; // Polymorphic: Can be Player or Comp
    Player *p2; // Polymorphic: Can be Player or Comp
    bool turn;
    bool clr;  // Flag set when memory dynamically allocated

    // Methods
    void doTurn();

public:
    Game(string uid);
    Game(Player *p1, Player *p2, string uid);
    bool play();
    ~Game();
    
    
    //Accessors
    string getUID();
    Player* getP1();
    Player* getP2();
    
    //Serialization
    void serialize(stringstream&);
    void deserialize(fstream&);
};

#endif /* GAME_H */
