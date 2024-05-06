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
    
    shipHealth['C'] =5; // Hp for a carrier
    shipHealth['B'] =4; // Hp for a batteship
    shipHealth['D'] =3; // Hp for a destroyer
    shipHealth['S'] =3; // Hp for a submarine
    shipHealth['P'] =2; // Hp for a patrol boat
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

char Player::getBoard(int row, int col)
{
    return board[row][col];
}

char Player::getShots(int row, int col)
{
    return shots[row][col];
}

int Player::convToInt(string input) // done
{
    char row = input[0];
    row = tolower(row);
    int col = (input[1] - '0') - 1;
    int total = 0;

    // if player chooses column 10, add 9 to col -- col only checks first digit initially
    if ((input[1] - '0') == 1 && (input[2] - '0') == 0)
        col += 9;

    switch (row)
    {
        // A through J for 10x10 grid
    case 'a':
        total += col;
        break;
    case 'b':
        total = 10 + col;
        break;
    case 'c':
        total = 20 + col;
        break;
    case 'd':
        total = 30 + col;
        break;
    case 'e':
        total = 40 + col;
        break;
    case 'f':
        total = 50 + col;
        break;
    case 'g':
        total = 60 + col;
        break;
    case 'h':
        total = 70 + col;
        break;
    case 'i':
        total = 80 + col;
        break;
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
    char rowLabel[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    
    cout << "   1 2 3 4 5 6 7 8 9 10" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        cout << rowLabel[i] << "  ";
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
    char rowLabel[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    
    cout << "   1 2 3 4 5 6 7 8 9 10" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        cout << rowLabel[i] << "  ";
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
            setBoard(row, j, shipType);
            unsunk++;
        }
    }
    else
    { // direction == 'V'
        for (int i = row; i < row + size; ++i)
        {
            setBoard(i, col, shipType);
            unsunk++;
        }
    }

    shipCounts[shipType]--;
//    displayBoard(); // Display the board after each placement
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
            safeGetLine(input, 4);
            cout << "Enter direction (H for horizontal, V for vertical): ";
            direction = getSingleChar();
            direction = toupper(direction);
            location = Player::convToInt(input);
            int row = location / 10, col = location % 10;
            if (placeShip(row, col, size, direction, shipType))
            {
                cout << "Ship placed successfully!" << endl;
                displayBoard();
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
    char shipType;
    
    if (enemy->board[row][col] == SHIP_CELL)
    {
        cout << "Hit!" << endl;
        shipType = enemy->board[row][col];      // this will return the char at those coordinates which will decrement  
        enemy->setBoard(row, col, HIT_CELL);    // the appropriate ship, wont have to worry about the hit char taking over
        setShots(row, col, HIT_CELL);           // because we're looking for the ship's char before the board is updated 
        shipHealth[shipType]--;                 // a hit marker
        if(shipHealth[shipType]==0){
         cout << shipType << " was sunk!\n";    
        }
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
     * int:                 unsunk integer value
     */
    
    // Store object type to aid in deserialization
    short unsigned int type = static_cast<short unsigned int>(TYPE);
    buffer.write(reinterpret_cast<char*>(&type), sizeof(type));
    size += sizeof(type);

    //// Store each of the arrays (board, shots)
    
    // Store size of the board.
    int board_size = BOARD_SIZE;
    buffer.write(reinterpret_cast<char*>(&board_size), sizeof(board_size));
    size += sizeof(board_size);
    
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

    //// Store unordered_map (shipCounts)
    
    // Store size of unordered_map
    int map_count = shipCounts.size();
    buffer.write(reinterpret_cast<char*>(&map_count), sizeof(map_count));
    size += sizeof(map_count);
    
    // Store each key, value pair
    for (const pair<char, int> &kv : shipCounts)
    {
        //        cout << kv.first << " : " << kv.second << "\n";  //DEBUG
        buffer.write(reinterpret_cast<const char*>(&kv.first), sizeof(kv.first));
        buffer.write(reinterpret_cast<const char*>(&kv.second), sizeof(kv.second));
    }
    size += map_count * (sizeof(char) + sizeof(int));
    
    // Store unsunk integer value
    buffer.write(reinterpret_cast<char*>(&unsunk), sizeof(unsunk));
    size += sizeof(unsunk);
}

void Player::deserialize(fstream& file) {
    
    int board_size, map_count;
    
    //// Read each of the arrays (board, shots)

    // Read size of the board.
    file.read(reinterpret_cast<char*>(&board_size), sizeof(board_size));
    // Read board
    for (int r = 0; r < board_size; r++)
    {
        for (int c = 0; c < board_size; c++)
        {
            file.read(reinterpret_cast<char *>(&board[r][c]), sizeof(char));
        }
    }
    // Read shots
    for (int r = 0; r < board_size; r++) {
        for (int c = 0; c < board_size; c++) {
            file.read(reinterpret_cast<char*>(&shots[r][c]), sizeof(char));
        }
    }
    
    //// Read unordered_map (shipCounts)
    // Read size of unordered_map
    file.read(reinterpret_cast<char*>(&map_count), sizeof(map_count));
    // Read each key, value pair
    char key;
    int val;
    for (int i = 0; i < map_count; i++) {
        file.read(reinterpret_cast<char*>(&key), sizeof(key));
        file.read(reinterpret_cast<char*>(&val), sizeof(val));
        shipCounts[key] = val;
    }
    
    // Read unsunk integer value
    file.read(reinterpret_cast<char*>(&unsunk), sizeof(unsunk));
}