#include "board.h"

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}

 
/*
 * Returns true if the game is finished; false otherwise. The game is finished 
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) return true;
        }
    }
    return false;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == NULL) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A NULL move means pass.
    if (m == NULL) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}


/*
 * Returns the score that will result from making Move m on the board. The 
 * following simple heuristic function determines the score:
 * score = (# of our pieces) - (# of other side's pieces)
 */
int Board::get_simple_score(Move *move, Side moving_side, Side scoring_side) {
    // Make a copy of the current board for use only in this function
    Board *tempBoard = this->copy();
    // Do given move on this board
    tempBoard->doMove(move, moving_side);
    int score;
    // Check which side we are on and calculate score
    if (scoring_side == BLACK) {
        score = tempBoard->countBlack() - tempBoard->countWhite();
    }
    else {
        score = tempBoard->countWhite() - tempBoard->countBlack();
    }
    return score;
}

/*
 * Returns the score that will result from making Move m on the board. The 
 * following simple heuristic function determines the score, in addition to
 * several other considerations for special spaces (corners and edges):
 * score = (# of our pieces) - (# of other side's pieces)
 */
int Board::get_complex_score(Move *move, Side moving_side, Side scoring_side) {
    // Make a copy of the current board for use only in this function
    Board *tempBoard = this->copy();
    // Do given move on this board
    tempBoard->doMove(move, moving_side);
    int score;
    // Check which side we are on and calculate score
    if (scoring_side == BLACK) {
        score = tempBoard->countBlack() - tempBoard->countWhite();
    }
    else {
        score = tempBoard->countWhite() - tempBoard->countBlack();
    }
    // Apply further multipliers for moves in certain spaces
    // Bonus for corners:
    if ((move->x == 0 && move->y == 0) || (move->x == 0 && move->y == 7) ||
        (move->x == 7 && move->y == 0) || (move->x == 7 && move->y == 7)) {
        if (moving_side == scoring_side) {
            score += 7;
        }
        else {
            score -= 7;
        }
    }
    // Bonus for edges next to corners which we own, penalty for edges next to 
    // unoccupied corners, or slight bonus for edges next to corners owned by
    // the other side
    // Top left
    else if ((move->x == 0 && move->y == 1) || (move->x == 1 && move->y == 0)) {
        if ((black[0 + 0 * 8] == 1 && scoring_side == BLACK) ||
            (taken[0 + 0 * 8] == 1 && black[0 + 0 * 8] == 0 
                                   && scoring_side == WHITE)) {
            score += 7;
        }
        else if ((black[0 + 0 * 8] == 1 && scoring_side == WHITE) ||
                 (taken[0 + 0 * 8] == 1 && black[0 + 0 * 8] == 0 
                                        && scoring_side == BLACK)) {
            score += 2;
        }
        else {
            score -= 5;
        }
    }
    // Top right
    else if ((move->x == 0 && move->y == 6) || (move->x == 1 && move->y == 7)) {
        if ((black[7 + 0 * 8] == 1 && scoring_side == BLACK) ||
            (taken[7 + 0 * 8] == 1 && black[7 + 0 * 8] == 0 
                                   && scoring_side == WHITE)) {
            score += 7;
        }
        else if ((black[7 + 0 * 8] == 1 && scoring_side == WHITE) ||
                 (taken[7 + 0 * 8] == 1 && black[7 + 0 * 8] == 0 
                                        && scoring_side == BLACK)) {
            score += 2;
        }
        else {
            score -= 5;
        }
    }
    // Bottom left
    else if ((move->x == 6 && move->y == 0) || (move->x == 7 && move->y == 1)) {
        if ((black[0 + 7 * 8] == 1 && scoring_side == BLACK) ||
            (taken[0 + 7 * 8] == 1 && black[0 + 7 * 8] == 0 
                                   && scoring_side == WHITE)) {
            score += 7;
        }
        else if ((black[0 + 7 * 8] == 1 && scoring_side == WHITE) ||
                 (taken[0 + 7 * 8] == 1 && black[0 + 7 * 8] == 0 
                                        && scoring_side == BLACK)) {
            score += 2;
        }
        else {
            score -= 5;
        }
    }  
    // Bottom right
    else if ((move->x == 7 && move->y == 6) || (move->x == 6 && move->y == 7)) {
        if ((black[7 + 7 * 8] == 1 && scoring_side == BLACK) ||
            (taken[7 + 7 * 8] == 1 && black[7 + 7 * 8] == 0 
                                   && scoring_side == WHITE)) {
            score += 7;
        }
        else if ((black[7 + 7 * 8] == 1 && scoring_side == WHITE) ||
                 (taken[7 + 7 * 8] == 1 && black[7 + 7 * 8] == 0 
                                        && scoring_side == BLACK)) {
            score += 2;
        }
        else {
            score -= 5;
        }
    }
    // Bonus for other edge spaces
    else if (move->x == 0 || move->x == 7 || move->y == 0 || move->y == 7) {
        if (moving_side == scoring_side) {
            score += 2;
        }
        else {
            score -= 2;
        }
    }
    return score;
}
