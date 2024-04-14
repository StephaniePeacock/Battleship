/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Player.cpp
 * Author: hanne
 * 
 * Created on April 13, 2024, 5:57 PM
 */

#include "Player.h"

Player::Player(bool guesses[], char ships[], bool turn, int fleet) {
    this->turn = turn;
    this->fleet = fleet;
    for (int i = 0; i < BOARDSIZE; ++i) {
        this->guesses[i] = guesses[i];
        this->ships[i] = ships[i];
    }
}




