/* 
 * File:   main.cpp
 * Authors: Anthony Bliss, Steven Contreres, Leoncio Hermosillo, 
 *          Isaiah Lopez, Carlos Moreno, Stephanie Peacock, Marco Reyes,  
 *          Matthew Rodriguez, Michael Hawara, Allen Yang, Hannes Ziegler  
 *
 * Created on April 19, 2024, 6:39 PM
 * Purpose: Simulate a website that plays Battleship
 */

 //System Libraries Are in Battleship.h

using namespace std;

//User Libraries
#include "Battleship.h"
//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set Random Number Seed Here
    srand(static_cast<unsigned int>(time(0)));
    //Declare all Variables Here

    //Input or initialize values Here

    //Launching Game
    Battleship app = Battleship();
    app.main();

    //Process/Calculations Here

    //Output Located Here

    //Exit
    return 0;
}