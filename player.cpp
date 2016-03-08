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
  try_move = NULL;

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
  // check if opponent's move was not NULL. 
  // If not, make their move on our board.
  std::cerr << "first\n";
  our_Board.doMove(opponentsMove, other_side);
  std::cerr << "second\n";
  // If we have no possible moves, return NULL:
  //if (not(our_Board.hasMoves(our_side))) {
    //return NULL;
  //}
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) { 
      std::cerr << "third\n";
      Move temp_move = Move(i, j);
      std::cerr << "fourth\n";
      try_move = &temp_move;
      //try_move = &Move(i, j);
      std::cerr << "trying a move:\n";
      if (our_Board.checkMove(try_move, our_side)) {
        our_Board.doMove(try_move, our_side);  
        std::cerr << "returning a move:\n";
	    return try_move;
      }
    }
  }
  std::cerr << "null?\n";
  return NULL;
}


// attempts at implementing simple heuristic


/*    
std::unordered_map<Move*, int> score_map;
for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) { 
        *try_move = Move(i, j);
        if (our_Board.checkMove(try_move, our_side)) {
            int score = get_simple_score(try_move, our_side);
            std::pair<*Move, int> to_add(*try_move, our_side);
            score_map.insert(to_add);
        }
    }
}
unordered_map<Move*, int>::iterator it;
int best_score = 0;
Move* best_move;
for (it = score_map.begin; it != score_map.end; it++) {
    if (it->second > best_score) {
        best_score = it->second;
        best_move = it->first;
    }
}
return best_move;
*/    








