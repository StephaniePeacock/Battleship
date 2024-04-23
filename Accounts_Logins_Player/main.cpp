/* 
 * File:   main.cpp
 * Author: Steven 
 *
 * Created on April 19, 2024, 6:39 PM
 */

 //System Libraries Here
#include <iostream>  //Input/Output Library
#include <iomanip>   //Format Library
#include <cstdlib>  
#include <ctime>
#include <fstream>

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