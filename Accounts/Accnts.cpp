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
    }
    else
    {
        cout << "File \"" << fname << "\" already exists.\n";
    }
    file.close();
}

int Accnts::count() {
    
    // Get size of file
    file.seekg(0L, ios::end);
    int fbytes = file.tellg();
    
    // Get size of record
    int rbytes = sizeof(User);
    
    // Calculate and return number of records in database
    return fbytes / rbytes;
}

/// @brief Add a new user record to the database.
/// @param user The user record to add.
void Accnts::add(const User* user)
{
//    user.display();  //DEBUG
    file.seekp(0L, ios::end);
    file.write(reinterpret_cast<const char*>(user), sizeof(User));
    file.flush();
}

/// @brief Find a user record in the database.
/// @param email The email of the user record to find.
/// @return The index position of the record in the database.
int Accnts::fnd(string email)
{
    int i = 0;
    int pos = -1;
    int end = count();
    User* current = nullptr;
//    cout << "Searching for " << email << "\n";  //DEBUG

    while (i < end) {
//        cout << "Searching user #" << i << "\n";  //DEBUG
        current = get(i);
        if (current->email == email) {  //account found
            pos = i;
            break; 
        }
        i++;
    }
    return pos;
}

/// @brief Get a user recrod from the database.
/// @param pos The index position of the user record to get.
/// @return The record of the found user. WARNING: Returns dynamically allocated memory.
User* Accnts::get(int pos)
{
    User* acct = new User;
    
    long int cur = pos * sizeof(User);
    file.seekg(cur, ios::beg);
    file.read(reinterpret_cast<char*>(acct), sizeof(User));
    return acct;
}

/// @brief Get all user records from the database.
/// @return A pointer to an array of user records.
User* Accnts::geta()
{
    int end = count();
    User* users = new User[count()];
    file.seekg(0L, ios::beg);
    for (int i = 0; i < end; i++){
        file.read(reinterpret_cast<char*>(&users[i]), sizeof(User));
    }
    return users;
}

/// @brief Set the given record at the given index in the database.
/// @param  pos The index position of the record to set.
/// @param  user The user record to set.
void Accnts::set(int pos, const User* user)
{
    long int cur = pos * sizeof(User);
    file.seekp(cur, ios::beg);
    file.write(reinterpret_cast<const char*>(user), sizeof(User));
    file.flush();
}

/// @brief Delete the record at the given index in the database.
/// @param pos The index position of the user record to delete.
void Accnts::del(int pos)
{
    
}
