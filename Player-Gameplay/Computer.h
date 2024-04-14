#include <string>
using namespace std;

#include "Player.h"

class Computer : public Player
{
public:
    int compTurn();
};