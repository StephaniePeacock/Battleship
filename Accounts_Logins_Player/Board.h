/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Board.h
 * Author: hanne
 *
 * Created on April 14, 2024, 11:17 AM
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>

const int BOARD_SIZE = 10;
const char EMPTY_CELL = '-';
const char SHIP_CELL = 'S';
const char HIT_CELL = 'X';
const char MISS_CELL = 'O';

const std::vector<std::pair<char, int>> SHIP_SIZES = {
    {'C', 5},  //Carrier
    {'B', 4},  //Battleship
    {'D', 3},  //Destroyer
    {'S', 3},  //Submarine
    {'P', 2}   //Patrol Boat
};

#endif /* BOARD_H */

