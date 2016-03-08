#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

private:
  
  Side our_side;
  Side other_side;
  Move* try_move;

public:
    Board our_Board;
    Player(Side side);
    Player(Side side, Board *board);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
