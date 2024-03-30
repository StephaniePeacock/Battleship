/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/*
 * File:   Accnts.cpp
 * Author: hanne
 *
 * Created on March 30, 2024, 7:42 AM
 */

#include "Accnts.h"

Accnts::Accnts(string fname)
{
    this->fname = fname;
}

/// @brief Open file stream.
void Accnts::open()
{
    file.open(fname, std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        cout << "Error opening file: " << fname << std::endl;
    }
}

/// @brief Close file stream.
void Accnts::close()
{
    file.close();
}

/// @brief Create a new database.
/// @param fname The path to the new database.
void Accnts::create(string fname)
{

    // check file existence, create if doesn't exist
    fstream file;
    file.open(fname, ios::in | ios::binary);
    if (!file)
    {
        file.close();
        file.open(fname, ios::out | ios::binary);
    } else {
        cout << "File \"" << fname << "\" already exists.\n";
    }
    file.close();
}

/// @brief Add a new user record to the database.
/// @param New record.
void add(const User *)
{
    
}
