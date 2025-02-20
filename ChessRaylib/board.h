#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"
#include <vector>
#include "Move.h"

class Board {
public:
    static const int BOARD_SIZE = 8;
    static const int SQUARE_SIZE = 80;

    Board(int boardArray[64]);
    void Draw() const;
    int TryToGetSquareUnderMouse(int mouseX, int mouseY);
    void SetSelectedPiece(int piece, int pieceIndex);
    std::vector<int> CalculateLegalMoves(int pieceIndex);
    void MakeMove(Move move);
    int FindPieceIndex(int piece) const;
    int getKingPosition(int color) const;

     // Operator[] to access board elements
    int operator[](int index) const;

    int& operator[](int index);

    int selectedPiece;
    int selectedPieceIndex;

private:
    int board[64];
    
    std::vector<int> legalMoves;
};

#endif // BOARD_H
