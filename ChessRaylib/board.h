#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"

class Board {
public:
    static const int BOARD_SIZE = 8;
    static const int SQUARE_SIZE = 60;

    Board(int board[64]);
    void Draw() const;

private:
    int board[64];
};

#endif // BOARD_H
