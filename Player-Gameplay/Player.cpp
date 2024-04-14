#include <iostream>
#include <string>
using namespace std;

#include "Player.h"

Player::Player()
{
    *totalShipHealth = 17;
    place();
}

Player::Player(Ship *[], int *[]) // For loading a game
{
}

Player::~Player()
{
}

void Player::place() // print board if coords are invalid/after a placement
{
    {
        int sizes[SHIPS_NUM] = { 5, 4, 3, 3, 2 };
        string names[SHIPS_NUM] = { "Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer" };
        string bow = "";
        int convert = 0;
        char layout;

        // initialize ships.coords with temp values
        for (int i = 0; i < SHIPS_NUM; i++)
        {
            // MUST DELETE LATER
            ships[i].coord = new int[sizes[i]];

            for (int j = 0; j < sizes[i]; j++)
            {
                ships[i].coord[j] = -1;
            }
        }

        // entire loop gets coordinates for each size ship, validates, and assigns coords to ship struct
        for (int i = 0; i < SHIPS_NUM; i++)
        {
            cout << "\nPlacing " << names[i] << " (" << sizes[i] << ") squares" << endl;

            cout << "Enter coordinates for the bow of the ship" << endl;
            cin >> bow;

            // convert input to number and validate (example: e5 = 44)
            convert = convInt(bow);
            while (convert == -1)
            {
                cout << "Enter coordinates for the bow of the ship " << endl;
                cin >> bow;
                convert = convInt(bow);
            }

            cout << "Choose Layout - Horizontal or Vertical (h/v)" << endl;
            cin >> layout;

            // function makes sure ship does not go out of bounds or wrap around
            // example: 5 length ship placed at g10 horizontally will not be valid
            isValid(bow, convert, layout, sizes[i]);

            // temp array to compare coords to other ships to check for overlaps before adding to ships.coord[]
            int* tempArr = new int[sizes[i]];

            addTemp(tempArr, layout, convert, sizes[i]);

            /*
                nested for loops to check if coordinates overlap
                first loop: reversed loop to go through current ship and previous ships (ship3 should check overlaps against ship2 and ship1)
                second loop: go through each element of the ships coord array
                third loop: check coords in tempArr against element in the ship to check for overlaps
            */
            for (int j = i; j >= 0; j--)
            {
                bool overlap = false;

                for (int shipEle = 0; shipEle < sizes[j]; shipEle++)
                {
                    for (int tempEle = 0; tempEle < sizes[j]; tempEle++)
                    {
                        do {
                            if (tempArr[tempEle] == ships[j].coord[shipEle])
                            {
                                overlap = true;

                                cout << "Invalid Placement: Overlaps another ship." << endl;
                                cout << "Choose another starting location" << endl;
                                cin >> bow;

                                convert = convInt(bow);
                                while (convert == -1)
                                {
                                    cout << "Enter coordinates for the bow of the ship " << endl;
                                    cin >> bow;
                                    convert = convInt(bow);
                                }

                                addTemp(tempArr, layout, convert, sizes[i]);
                            }
                            else {
                                overlap = false;
                            }
                        } while (overlap);
                    }

                    if (overlap)
                        break;

                    // fill current ship with validated coords
                    ships[i].coord[shipEle] = tempArr[shipEle];
                }
            }

            ships[i].length = sizes[i];
            ships[i].health = sizes[i];

            delete[] tempArr;
        }
    }
}

int Player::playerTurn()
{
}

bool Player::isHit(int)
{
}

int Player::convToInt(string input) // done
{
    char row = input[0];
    int col = (input[1] - '0') - 1;
    int total = 0;

    // if player chooses column 10, add 9 to col -- col only checks first digit initially
    if ((input[1] - '0') == 1 && (input[2] - '0') == 0)
        col += 9;

    switch (row)
    {
        // A through J for 10x10 grid
    case 'A':
    case 'a':
        total += col;
        break;
    case 'B':
    case 'b':
        total = 10 + col;
        break;
    case 'C':
    case 'c':
        total = 20 + col;
        break;
    case 'D':
    case 'd':
        total = 30 + col;
        break;
    case 'E':
    case 'e':
        total = 40 + col;
        break;
    case 'F':
    case 'f':
        total = 50 + col;
        break;
    case 'G':
    case 'g':
        total = 60 + col;
        break;
    case 'H':
    case 'h':
        total = 70 + col;
        break;
    case 'I':
    case 'i':
        total = 80 + col;
        break;
    case 'J':
    case 'j':
        total = 90 + col;
        break;
    default:
        total = -1;
    }

    // 99 is the only square where horizontal/vertical ships cannot be placed with min ship size of 2
    if (total >= 99)
        total = -1;

    return total;
}

void isValid(string& bow, int& convert, char& layout, int num) // done
{
    while (true)
    {
        if (layout == 'H' || layout == 'h')
        {
            // formula to determine if ship goes out of bounds horizontally
            while ((convert / 10) != ((convert + num) / 10))
            {
                cout << "Invalid placement" << endl;

                cout << "Enter coordinates for the bow of the ship " << endl;
                cin >> bow;
                convert = convInt(bow);
            }
            break;
        }
        else if (layout == 'V' || layout == 'v')
        {
            // formula to determine if ship goes out of bounds vertically
            while (convert + (10 * (num - 1)) > 99)
            {
                cout << "Invalid placement" << endl;

                cout << "Enter coordinates for the bow of the ship " << endl;
                cin >> bow;
                convert = convInt(bow);
            }
            break;
        }
        else
        {
            cout << "Invalid input, enter 'h' for horizontal or 'v' for vertical." << endl;
            cin >> layout;
        }
    }
}

void addTemp(int* tempArr, char layout, int convert, int num) // done
{
    // set the first element to chosen coordinate
    tempArr[0] = convert;

    // fill tempArr with coords corresponding to the size and layout of the ship
    for (int i = 1; i < num; i++)
    {
        if (layout == 'H' || layout == 'h')
            tempArr[i] = convert + i;
        else if (layout == 'V' || layout == 'v')
            tempArr[i] = convert + (10 * i);
    }
}

int Player::getHealth()
{
    return *totalShipHealth;
}

int *Player::getGuesses()
{
    return guesses;
}