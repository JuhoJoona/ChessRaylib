#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"
#include <vector>

class Board {
public:
    static const int BOARD_SIZE = 8;
    static const int SQUARE_SIZE = 80;

    Board(int boardArray[64]);
    void Draw() const;
    int TryToGetPieceUnderMouse(int mouseX, int mouseY);
    void SetSelectedPiece(int index);
    std::vector<int> CalculateLegalMoves(int pieceIndex);

     // Operator[] to access board elements
    int operator[](int index) const;

    int& operator[](int index);

private:
    int board[64];
    int selectedPieceIndex;
    std::vector<int> legalMoves;
};

#endif // BOARD_H
