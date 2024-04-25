/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/*
 * File:   Player.cpp
 * Author: hanne
 *
 * Created on April 14, 2024, 11:15 AM
 */

#include "Player.h"

Player::Player()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            board[i][j] = EMPTY_CELL;
            shots[i][j] = EMPTY_CELL;
        }
    }
    shipCounts['C'] = 1; // Carrier
    shipCounts['B'] = 2; // Battleship
    shipCounts['D'] = 3; // Destroyer
    shipCounts['S'] = 3; // Submarine
    shipCounts['P'] = 4; // Patrol Boat
    unsunk = 0;
}

Player::~Player()
{
}

void Player::setBoard(int row, int col, const char c)
{
    board[row][col] = c;
}

void Player::setShots(int row, int col, const char c)
{
    shots[row][col] = c;
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

// Function to display the current state of the board
void Player::displayBoard()
{
    cout << "   A B C D E F G H I J" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        cout << i << "  ";
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// display shots taken (based on opponent's board)
void Player::displayShots()
{
    cout << "   A B C D E F G H I J" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        cout << i << "  ";
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            cout << shots[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if a ship can be placed at the given coordinate
bool Player::isValidPlacement(int row, int col, int size, char direction)
{
    if (!isValidCoordinate(row, col) || (direction != 'H' && direction != 'V'))
        return false;

    if (direction == 'H')
    {
        if (col + size - 1 >= BOARD_SIZE)
            return false;
        for (int j = col; j < col + size; ++j)
        {
            if (board[row][j] == SHIP_CELL)
                return false;
        }
    }
    else
    { // direction == 'V'
        if (row + size - 1 >= BOARD_SIZE)
            return false;
        for (int i = row; i < row + size; ++i)
        {
            if (board[i][col] == SHIP_CELL)
                return false;
        }
    }

    return true;
}

// Function to place a ship on the board
bool Player::placeShip(int row, int col, int size, char direction, char shipType)
{
    if (shipCounts[shipType] <= 0 || !isValidPlacement(row, col, size, direction))
    {
        cout << "Invalid placement!" << endl;
        return false;
    }

    if (direction == 'H')
    {
        for (int j = col; j < col + size; ++j)
        {
            setBoard(row, j, SHIP_CELL);
            unsunk++;
        }
    }
    else
    { // direction == 'V'
        for (int i = row; i < row + size; ++i)
        {
            setBoard(i, col, SHIP_CELL);
            unsunk++;
        }
    }

    shipCounts[shipType]--;
    displayBoard(); // Display the board after each placement
    return true;
}

// Function to prompt the user to place ships on the board
void Player::promptShipPlacement()
{
    char shipTypes[] = {'C', 'B', 'D', 'S', 'P'};
    for (char shipType : shipTypes)
    {
        int size = shipType == 'C' ? 5 : shipType == 'B' ? 4
                                     : shipType == 'D'   ? 3
                                     : shipType == 'S'   ? 3
                                                         : 2;
        cout << "Placing " << size << "-unit " << shipType << " ship." << endl;
        while (true)
        {
            int location;
            string input;
            char letter;
            char direction;
            cout << "Enter starting coordinates. (Ex. B4)" << endl;
            cin >> input;
            cout << "Enter direction (H for horizontal, V for vertical): ";
            cin >> direction;
            location = convToInt(input);
            int row = location / 10, col = location % 10;
            if (placeShip(row, col, size, direction, shipType))
            {
                cout << "Ship placed successfully!" << endl;
                break;
            }
            else
            {
                cout << "Invalid coordinates or ship placement. Try again." << endl;
            }
        }
    }
}

// Function to attack a cell on the opponent's board
void Player::attackCell(int row, int col, Player *enemy)
{
    if (enemy->board[row][col] == SHIP_CELL)
    {
        cout << "Hit!" << endl;
        enemy->setBoard(row, col, HIT_CELL);
        setShots(row, col, HIT_CELL);
    }
    else
    {
        cout << "Miss!" << endl;
        enemy->setBoard(row, col, MISS_CELL);
        setShots(row, col, MISS_CELL);
    }
}

void Player::serialize(stringstream &buffer, int &size)
{
    /* --Player serialization binary storage structure--
     * short unsigned int:  type of object (Player=0, Comp=1)
     * int:                 size of board
     * char[board size]:    char for each item in board array
     * char[board size]:    char for each item in shots array
     * int:                 shipCounts map count
     * char & int pars:     first key (char) then value (int)
     *                        for each pair in map
     */

    // Store object type to aid in deserialization
    short unsigned int type = static_cast<short unsigned int>(TYPE);
    buffer.write(reinterpret_cast<char *>(&type), sizeof(type));
    size += sizeof(type);

    // Store each of the arrays (board, shots)
    // Store size of the board.
    int board_size = BOARD_SIZE;
    buffer.write(reinterpret_cast<char *>(&board_size), sizeof(board_size));
    // Store board
    for (int r = 0; r < board_size; r++)
    {
        buffer.write(board[r], sizeof(board[r]));
    }
    // Store shots
    for (int r = 0; r < board_size; r++)
    {
        buffer.write(shots[r], sizeof(shots[r]));
    }
    size += board_size * board_size * sizeof(char) * 2;

    // Store unordered_map (shipCounts)
    // Store size of unordered_map
    int map_count = shipCounts.size();
    buffer.write(reinterpret_cast<char *>(&map_count), sizeof(map_count));
    // Store each key, value pair
    for (const pair<char, int> &kv : shipCounts)
    {
        //        cout << kv.first << " : " << kv.second << "\n";  //DEBUG
        buffer.write(reinterpret_cast<const char *>(&kv.first), sizeof(kv.first));
        buffer.write(reinterpret_cast<const char *>(&kv.second), sizeof(kv.second));
    }
    size += map_count * (sizeof(char) + sizeof(int));
}

void Player::deserialize(stringstream& buffer) {
    
    int board_size, map_count;
    
    // Read each of the arrays (board, shots)
    // Read size of the board.
    buffer.read(reinterpret_cast<char*>(&board_size), sizeof(board_size));
    cout << "BOARD_SIZE: " << board_size << "\n";
    // Read board
    for (int r = 0; r < board_size; r++)
    {
        for (int c = 0; c < board_size; c++)
        {
            buffer.read(reinterpret_cast<char *>(&board[r][c]), sizeof(char));
        }
    }
    for (int r = 0; r < board_size; r++) {
        for (int c = 0; c < board_size; c++) {
            buffer.read(reinterpret_cast<char*>(&shots[r][c]), sizeof(char));
        }
    }
    
    // Read unordered_map (shipCounts)
    // Read size of unordered_map
    buffer.read(reinterpret_cast<char*>(&map_count), sizeof(map_count));
    // Read each key, value pair
    char key;
    int val;
    for (int i = 0; i < map_count; i++) {
        buffer.read(reinterpret_cast<char*>(&key), sizeof(key));
        buffer.read(reinterpret_cast<char*>(&val), sizeof(val));
        shipCounts[key] = val;
    }
}