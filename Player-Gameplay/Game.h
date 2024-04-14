#include <cstring>
using namespace std;

#include "Computer.h"

class Game
{
private:
    Player *p1;
    Computer *p2;
    int *shipsHit = new int[100]; // Ships that the player has hit
    int *compHit = new int[100];  // Ships that the computer has hit

public:
    Game(); // Empty constructor, doesn't contain anything
    ~Game();
    int newGame();   // Starts a new game
    int loadGame();  // Loads an existing game
    void saveGame(); // Saves current game
    int playGame();  // Battleship GamePlay
    void printPlayerBoard();
};