#include <string>
using namespace std;

const int SHIPS_NUM = 5;

struct Ship
{
    int length;
    int *coord;
    int shipHealth;

    // need to set to null to avoid errors
    Ship() : coord(nullptr) {}
};

class Player
{
protected:
    int *totalShipHealth = new int(); // Must instantiate to 17 in Computer class
    int *guesses = new int[100];
    Ship *ships = new Ship[SHIPS_NUM];

public:
    Player();
    Player(Ship *[], int *[]);
    ~Player();
    void place();
    int playerTurn();
    bool isHit(int);
    int convToInt(string);
    void isValid(string&, int&, char&, int);
    void addTemp(int*, char, int, int);
    void printBoard();
    int getHealth();   // Must instantiate in Computer Class
    int *getGuesses(); // Must instantiate in Computer Class
};