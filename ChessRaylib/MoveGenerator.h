#pragma once

#include "raylib.h"
#include "piece.h"
#include "Move.h"
#include "board.h"
#include <vector>

class MoveGenerator {
public:
    std::vector<Move> GenerateMoves(const Board& board, int color);

private:
    void GenerateSlidingMoves(const Board& board, int startSquare, std::vector<Move>& moves, int pieceType);
    void GenerateKingMoves(const Board& board, std::vector<Move>& moves);
    void GeneratePawnMoves(const Board& board, std::vector<Move>& moves);
    void GenerateKnightMoves(const Board& board, std::vector<Move>& moves);
    void CalculateNumSquaresToEdge();
    bool IsSquareAttacked(const Board& board, int square, int attackingColor);

    int NumSquaresToEdge[64][8];
};
