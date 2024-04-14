#include <iostream>
#include <string>
using namespace std;

#include "Game.h"
Game::Game()
{
    ;
}

Game::~Game()
{
    delete p1;
    delete p2;
    p1 = nullptr;
    p2 = nullptr;
}

int Game::newGame()
{
    p1 = new Player();
    p2 = new Computer();

    return this->playGame();
}

int Game::loadGame()
{
    /// pretend we set everything already
    return this->playGame();
}

void Game::saveGame()
{
    // Not sure how this is handled yet
}

int Game::playGame()
{
    int i = 0;
    int j = 0;
    while (p1->getHealth() != 0 && p2->getHealth() != 0)
    {
        int numInput;
        do
        {
            numInput = p1->playerTurn();
            if (p2->isHit(numInput))
            {
                cout << "Hit!" << endl;
                shipsHit[i++] = numInput;
            }
            else
            {
                cout << "Miss!" << endl;
                break;
            }
        } while (p2->isHit(numInput));

        do
        {
            numInput = p2->compTurn();
            if (p1->isHit(numInput))
            {
                cout << "You've been hit!" << endl;
                compHit[i++] = numInput;
            }
            else
            {
                cout << "They missed!" << endl;
                break;
            }
        } while (p2->isHit(numInput));
    }

    if (p1->getHealth() != 0)
    {
        cout << "Congrats, you won! Score increased by +1" << endl;
        return 1;
    }
    else
    {
        cout << "Aww better luck next time!" << endl;
        return -1;
    }
}

void Game::printPlayerBoard()
{
}