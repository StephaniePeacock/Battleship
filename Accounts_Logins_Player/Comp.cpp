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


int Comp::serialize(stringstream& buffer) {
    return 0;
    //TODO
}

void Comp::deserialize(fstream& file) {
    //TODO
}


