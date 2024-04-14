/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Player.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 11:15 AM
 */

#include "Player.h"

Player::Player(char board[][BOARDSIZE], char shots[][BOARDSIZE], bool turn, int fleet) {
    this->turn = turn;
    this->fleet = fleet;
    for (int x = 0; x < BOARDSIZE; ++x) {
        for (int y = 0; y < BOARDSIZE; ++y) {
            this->board[x][y] = board[x][y];
            this->shots[x][y] = shots[x][y];
        }
    }
}

