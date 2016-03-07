#include "player.h"
#include <assert.h>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    // Hi Mara Green!
    our_side = side;
    other_side = (our_side == BLACK) ? WHITE : BLACK;
    our_Board = Board();

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's move before calculating your own move
     */ 

  // check if oponent's move was not NULL. 
  // If not, make their move on our board.
  if (not(opponentsMove == NULL)) {
    our_Board.doMove(opponentsMove, other_side);
  }

  // If we have no possible moves, return NULL:
  if (not(our_Board.hasMoves(our_side))) {
    return NULL;
  }

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      Move try_move = Move(i, j);
      if (our_Board.checkMove(&try_move, our_side)) {
	return &try_move;
      }
    }
  }
  
  return NULL;
}
