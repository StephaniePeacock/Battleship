/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   GamesDB.h
 * Author: hanne
 *
 * Created on April 21, 2024, 1:51 PM
 */

#ifndef GAMESDB_H
#define GAMESDB_H

#include <fstream>

using namespace std;

#include "Game.h"

class GamesDB {
private:
    // Member variables
    string fname;
    fstream file;    
public:
    GamesDB();

};

#endif /* GAMESDB_H */

