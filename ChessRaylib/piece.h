#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"

class Piece {
public:
    static const int None = 0;
    static const int King = 1;
    static const int Pawn = 2;
    static const int Knight = 3;
    static const int Bishop = 5;
    static const int Rook = 6;
    static const int Queen = 7;

    static const int White = 8;
    static const int Black = 16;

    static const int typeMask = 0b00000111;
    static const int whiteMask = 0b00001000;
    static const int blackMask = 0b00010000;
    static const int hasMovedMask = 0b00100000;
    static const int isCheckedMask = 0b01000000;

    static int Color(int piece);
    static int PieceType(int piece);
    static bool IsRookOrQueen(int piece);
    static bool IsSlidingPiece(int piece);
    static bool IsType(int piece, int PieceToCompare);
    static bool IsColor(int piece, int color);
    static bool HasMoved(int piece);
    static bool IsChecked(int piece);
    static int SetHasMoved(int piece);
    static int SetChecked(int piece, bool checked);

private:
};

#endif // PIECE_H
