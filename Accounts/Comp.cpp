/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Comp.cpp
 * Author: hanne
 * 
 * Created on April 13, 2024, 5:57 PM
 */

#include "Comp.h"

Comp::Comp(char board[][BOARDSIZE], char shots[][BOARDSIZE], bool turn, int fleet, bool smart) 
    : Player(board, shots, turn, fleet), smart(smart) {
    this->smart = smart;
}


