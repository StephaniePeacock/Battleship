/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Comp.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 1:24 PM
 */

#include "Comp.h"

Comp::Comp() : Player() {
    this->smart = false;
}
Comp::Comp(bool smart) : Player() {
    this->smart = smart;
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
     */
    
    //// Serialize base class (Player) data
    
    Player::serialize(buffer, size);
    
    //// Serialize additional instance members unique to Comp
    
    // Store smart boolean value
    buffer.write(reinterpret_cast<char*>(&smart), sizeof(smart));
    size += sizeof(smart);
}

void Comp::deserialize(fstream& file) {
    
    //// Deserialize base class (Player) data
    
    Player::deserialize(file);
    
    //// Deserialize additional instance members unique to Comp
    
    // Read smart boolean value
    file.read(reinterpret_cast<char*>(&smart), sizeof(smart));
}