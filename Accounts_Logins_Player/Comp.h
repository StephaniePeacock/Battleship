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

class Comp : public Player {
private:
    bool smart;
    bool inCardinalSearch;


    // Stuff for dumb AI
    int state;      // States: 0 - Linear Search
                    //         1 - Narrowed Search
    int guesses;    // Number of guesses left
    int quadrant;   // Quadrant of the board to search
    int score;      // Score of the AI
    int consecutiveMisses;

    
public:
    const static PlayerType TYPE = PlayerType::COMP;
    Comp();
    Comp(bool smart);

    // These functions are virtual in the base class
    void placeShips();
    void shoot(int, int, Player *);

    // Accessor functions
    // void smartAI(int&, int&, Player*);

    // Dumb AI functions
    void dumbAI(int&, int&, Player*);
    void smartAI(int&, int&, Player*);
    void linSearch(int&, int&, Player*);
    void cardinalSearch(int&, int&, Player*);
    void attackPosition(int&, int&, Player*);
    int quadrantDetector(int, int, int, int);
    
    bool movesAvailable(int);
    bool getRandomPointInQuadrant(int, int, int, int&, int&);
    bool isValid(int&, int&, Player*);
    bool isGameOver();

    // Serialization functions
    void serialize(stringstream&, int&) override;
    void deserialize(fstream&) override;
};

#endif /* COMP_H */

