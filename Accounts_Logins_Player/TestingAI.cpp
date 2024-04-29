
#include "Board.h"
#include "Player.h"
#include "Comp.h"
#include "Game.h"
#include <iostream>
#include <string>


using namespace std;

int main() {
    Player p1 = Player();
    Player p2 = Player();

    Game game = Game(&p1, &p2, "1234");

    //game.testPlay();    // Modify to .testPLAY() to test


    return 0;
}