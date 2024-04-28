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
public:
    const static PlayerType TYPE = PlayerType::COMP;
    Comp();
    Comp(bool smart);
    void serialize(stringstream&, int&) override;
    void deserialize(fstream&) override;
};

#endif /* COMP_H */

