/* 
 * File:   Battleship.h
 * Author: Stephanie Peacock
 * Created on March 23, 2024, 9:38 PM
 * Purpose: Battleship Class Specification
 */

using namespace std;

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

class Battleship {
private:
    char choice;
public:
    Battleship();
    virtual ~Battleship(){}
    //Other Functions
    void login();
    void reg();
    bool checkEm(string);
    bool checkPw(string);
    bool verify(string, string);
};

#endif /* BATTLESHIP_H */

