#ifndef MOVE_H
#define MOVE_H

#include "raylib.h"
#include "piece.h" // Assuming Piece enum is defined here or included properly

class Move {
public:
    Move(int startingSquare, int targetSquare)
        : StartingSquare(startingSquare), TargetSquare(targetSquare) {}

    int StartingSquare;
    int TargetSquare;

private:
    // Add any private members or methods if necessary
};

#endif // MOVE_H
