#include "player.h"
#include <map>
#include <vector>



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
// Move *Player::doMove(Move *opponentsMove, int msLeft) {
//   // Make opponent's move on the board:
//   our_Board.doMove(opponentsMove, other_side);
//   // Return NULL if there are no possible moves:
//   if (not(our_Board.hasMoves(our_side))) {
//       return NULL;
//   }
//   // Now find our next move:
//   // Map of possible first moves and the maximum minimum score which will result
//   // from it after one more move
//  std::map<Move, int> minimum_map;
//   // Iterate through all possible first moves
//   for (int i = 0; i < 8; i++) {
//     for (int j = 0; j < 8; j++) { 
//       try_move = Move(i, j);
//       // Check that this is a valid move
//       if (our_Board.checkMove(try_move, our_side)) {
//           // Create a copy of this board to try further moves
//           Board *temp_Board = our_Board.copy();
//           // Do first move on this board
//           temp_Board->doMove(try_move, our_side);
//           // Vector of scores possible from next possible moves
//           std::vector<int> possible_scores;
//           // Iterate through possible next moves
//           for (int i = 0; i < 8; i++) {
//               for (int j = 0; j < 8; j++) { 
//                   Move try_next_move = Move(i, j);
//                   // Check validity
//                   if (our_Board.checkMove(try_next_move, other_side)) {
//                       // Calculate result of this second move
//                       int score = temp_Board->get_simple_score(try_next_move, other_side);
//                       possible_scores.push_back(score);
//                   }
//               }
//           }
//           // Find smallest of these scores
//           int smallest_score = 65;
//           for (unsigned int i = 0; i < possible_scores.size(); i++) {
//               if (possible_scores[i] < smallest_score) {
//                 smallest_score = possible_scores[i];
//               }
//           }
//           // Add the pair of this minimax score and first move to map
//           minimum_map.insert(std::pair<*Move, int> (try_move, smallest_score));
//        }
//     }
// }
// // Now that we have a map of first moves and corresponding smallest possible 
// // scores, we can find the move which gives the maximum minimum score
// std::map<Move, int>::iterator it;
// int max_score = 0;
// try_move = new Move(0, 0);
// for (it = minimum_map.begin; it != score_map.end; it++) {
//     if (it->second > max_score) {
//         max_score = it->second;
//         try_move = it->first;
//     }
// }
// our_Board.doMove(try_move, our_side);
// return try_move;
// }


// attempts at implementing simple heuristic

Move *Player::doMove(Move *opponentsMove, int msLeft) {
  our_Board.doMove(opponentsMove, other_side);
  try_move = NULL;
  Move * best_move = NULL;
  int best_score = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) { 
      try_move = new Move(i, j);
      if (our_Board.checkMove(try_move, our_side)) {
	int score = our_Board.get_simple_score(try_move, our_side);
	if (score > best_score) {
	  best_score = score;
	  best_move = try_move;
	}
      }
    }
  }
  our_Board.doMove(best_move, our_side);
  return best_move;
}



// attempts at implementing minimax shit








