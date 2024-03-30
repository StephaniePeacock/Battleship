/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Accnts.h
 * Author: hanne
 *
 * Created on March 30, 2024, 7:42 AM
 */

#ifndef ACCNTS_H
#define ACCNTS_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

#include "User.h"

class Accnts {
    public:
        // Member variables
        string fname;
        fstream file;
        // Member functions
        Accnts(string);
        void open();
        int count();
        static void create(string);
        void add(const User&);
        int fnd(string email);
        User get(int);  // Should we return pointer? downside: rem. to delete it later
        User* getAll();
        void set(int, const User*);
        void del(int);
        void close();
};

#endif /* ACCNTS_H */

