/*
 * File:   Game.cpp
 * Author: hanne
 *
 * Created on April 14, 2024, 1:44 PM
 */

#include "Game.h"

Game::Game()
{
    p1 = new Player();
    p1 = nullptr;
    p2 = new Player();
    p2 = nullptr;
    this->turn = false;
}

Game::Game(Player *p1, Player *p2)
{
    this->p1 = p1;
    this->p2 = p2;
    this->turn = false;
}

Game::~Game()
{
    // Sometimes we allocate new memory, conditionally clear it
    if (p1 == nullptr)
    {
        delete p1;
        p1 = nullptr;
    }
    if (p2 == nullptr)
    {
        delete p2;
        p2 = nullptr;
    }
}

/// @brief Update whose turn it is
void Game::doTurn()
{
    turn = !turn;
}
void Game::play()
{
    string input;
    int row, col;
    char letter;

    // Display player 1's board after ship placement
    cout << "Player 1's Board before ship placement:" << endl;
    p1->displayBoard();

    // Prompt player 1 to place ships on the board
    cout << "Player 1, please place your ships:" << endl;
    p1->promptShipPlacement();

    // Display player 1's board after ship placement
    cout << "Player 1's Board after ship placement:" << endl;
    p1->displayBoard();

    // Prompt player 2 to place ships on the board
    cout << "Player 2, please place your ships:" << endl;
    p2->promptShipPlacement();

    // Display player 2's board after ship placement
    cout << "Player 2's Board after ship placement:" << endl;
    p2->displayBoard();

    while (p2->getUnsunk() > 0 || p1->getUnsunk() > 0)
    {

        cout << "Commence attack. Enter row and col coordinates:" << endl;
        cin >> input;
        int location = convToInt(input);
        int row = location / 10;
        int col = location % 10;
        col = letter - 65;
        p1->attackCell(row, col, p2);
        p1->displayShots();
    }
}

void Game::serialize()
{
    stringstream p1_buff, p2_buff;
    int p1_size = 0, p2_size = 0;
    short unsigned int type_val; // DEBUG
    PlayerType type;             // DEBUG
    p2->attackCell(1, 1, p1);    // DEBUG  dummy shot to mod. board

    p1_buff.seekp(0L, std::ios_base::end);
    p2_buff.seekp(0L, std::ios_base::end);

    p1->serialize(p1_buff, p1_size);
    p2->serialize(p2_buff, p2_size);

    // Read the Player object type
    p1_buff.read(reinterpret_cast<char *>(&type_val), sizeof(type_val));
    type = static_cast<PlayerType>(type_val);
    cout << "TYPE: " << static_cast<int>(type) << "\n"; // DEBUG

    if (type == PlayerType::PLAYER)
    { // DEBUG
        Player *p1 = new Player();
        p1->deserialize(p1_buff);
    }
}

void Game::deserialize(fstream &file)
{
    //    /* Assumes that file stream read position is already set.
    //     *
    //     * Deserialize each polymorphic type by calling its own
    //     * deseralize method. Each one knows how to correctly load
    //     * its type's data from file.
    //     */
    //
    //    short unsigned int type_val;
    //    PlayerType type;
    //
    //    //// Deserialize p1 (Player 1)
    //
    //    // Read the Player object type
    //    file.read(reinterpret_cast<char*>(&type_val), sizeof(type_val));
    //    type = static_cast<PlayerType>(type_val);
    //
    //    // First clean up the old allocated memory for this->p1
    //    delete this->p1;
    //    this->p1 = nullptr;
    //
    //    // get new p1; Use appropriate serialization method for type
    //    switch (type) {
    //        case PlayerType::PLAYER: {
    //            Player* p1 = new Player();
    //            p1->deserialize(file);
    //            this->p1 = p1;
    //            break;
    //        }
    //        case PlayerType::COMP: {
    //            Comp* p1 = new Comp();
    //            p1->deserialize(file);
    //            this->p1 = p1;
    //            break;
    //        }
    //    }
    //
    //    //// Deserialize p2 (Player 2)
    //
    //    // First clean up the old allocated memory for this->p1
    //    delete this->p2;
    //    this->p2 = nullptr;
    //
    //    // Read the Player object type
    //    file.read(reinterpret_cast<char*>(&type_val), sizeof(type_val));
    //    type = static_cast<PlayerType>(type_val);
    //
    //    // get new p2; Use appropriate serialization method for type
    //    switch (type) {
    //        case PlayerType::PLAYER: {
    //            Player* p2 = new Player();
    //            p1->deserialize(file);
    //            this->p2 = p2;
    //            break;
    //        }
    //        case PlayerType::COMP: {
    //            Comp* p2 = new Comp();
    //            p1->deserialize(file);
    //            this->p2 = p2;
    //            break;
    //        }
    //    }
}
