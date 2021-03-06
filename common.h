#ifndef __COMMON_H__
#define __COMMON_H__

enum Side { 
    WHITE, BLACK
};

class Move {
   
public:
    int x, y;
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }
    Move() {
        this->x = 0;
        this->y = 0;        
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

struct scored_move {
    int score;
    Move move;
    scored_move() {
        this->score = 0;
        this->move = Move();
    }
};

#endif
