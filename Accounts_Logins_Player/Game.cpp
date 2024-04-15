/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Game.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 1:44 PM
 */

#include "Game.h"

Game::Game(Player* p1, Player* p2) {
    this->p1 = p1;
    this->p2 = p2;
    this->turn = false;
}


/// @brief Update whose turn it is
Game::doTurn() {
    turn = !turn;
}
