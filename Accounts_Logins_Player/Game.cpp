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

Game::Game(Player *p1, Player *p2, string uid)
{
    this->p1 = p1;
    this->p2 = p2;
    safeCStrNCpy(this->uid, uid, game::MAXSTR);
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
        int location = Player::convToInt(input);
        int row = location / 10;
        int col = location % 10;
        col = letter - 65;
        p1->attackCell(row, col, p2);
        p1->displayShots();
    }
}

void Game::serialize(stringstream& buffer)
{
    /* --Game serialization binary storage structure--
     * char[MAXSTR]:        Unique identifier (UID) of game
     *                      - Used to find game
     * int:                 size (in bytes) of game
     *                      - Used for seeking
     * bool:                current turn
     * Player:              Player 1
     * Player:              Player 2
     */
    stringstream p1_buff, p2_buff;
    int p1_size = 0, p2_size = 0, game_size = 0;
    
    // Serialize each Player object to a buffer
    p1_buff.seekp(0L, std::ios_base::end);
    p1->serialize(p1_buff, p1_size);
    p2_buff.seekp(0L, std::ios_base::end);
    p2->serialize(p2_buff, p2_size);
    
    // Store the unique identifier of the game
    buffer.write(reinterpret_cast<char*>(&uid), sizeof(uid));
    
    // Store the size of game (used for seeking)
    game_size = sizeof(bool) + p1_size + p2_size;
    buffer.write(reinterpret_cast<char*>(&game_size), sizeof(game_size));
    
    // Store the current turn
    buffer.write(reinterpret_cast<char*>(&turn), sizeof(turn));
    
    // Store Player 1
    string p1_str = p1_buff.str();
    buffer.write(p1_str.c_str(), p1_str.size());
    // Store Player 2
    string p2_str = p2_buff.str();
    buffer.write(p2_str.c_str(), p2_str.size());
}

void Game::deserialize(stringstream& buffer)
{
        /* Assumes that buffer stream read position is already set.
         *
         * Deserialize each polymorphic type by calling its own
         * deseralize method. Each one knows how to correctly load
         * its type's data from buffer.
         */
    
        short unsigned int type_val;
        PlayerType type;
        
        // Read the current turn
        buffer.read(reinterpret_cast<char*>(&turn), sizeof(turn));

        //// Deserialize p1 (Player 1)
        // First free up the old allocated memory for this->p1
        delete this->p1;
        this->p1 = nullptr;
        
        // Read the Player object type
        buffer.read(reinterpret_cast<char*>(&type_val), sizeof(type_val));
        type = static_cast<PlayerType>(type_val);
    
        // get new p1; Use appropriate serialization method for type
        switch (type) {
            case PlayerType::PLAYER: {
                Player* p1 = new Player();
                p1->deserialize(buffer);
                this->p1 = p1;
                break;
            }
            case PlayerType::COMP: {
                Comp* p1 = new Comp();
                p1->deserialize(buffer);
                this->p1 = p1;
                break;
            }
        }
    
        //// Deserialize p2 (Player 2)
        // First free up the old allocated memory for this->p2
        delete this->p2;
        this->p2 = nullptr;
    
        // Read the Player object type
        buffer.read(reinterpret_cast<char*>(&type_val), sizeof(type_val));
        type = static_cast<PlayerType>(type_val);
    
        // get new p2; Use appropriate serialization method for type
        switch (type) {
            case PlayerType::PLAYER: {
                Player* p2 = new Player();
                p1->deserialize(buffer);
                this->p2 = p2;
                break;
            }
            case PlayerType::COMP: {
                Comp* p2 = new Comp();
                p1->deserialize(buffer);
                this->p2 = p2;
                break;
            }
        }
}
