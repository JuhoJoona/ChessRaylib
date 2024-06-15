#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "raylib.h"
#include "piece.h"
#include "Move.h"
#include "board.h"
#include <vector>

class MoveGenerator {
public:

    std::vector<Move> GenerateMoves(const Board& board);

private:
    int NumSquaresToEdge[64][8];

    void CalculateNumSquaresToEdge();

    // Helper methods for generating moves of different piece types
    void GenerateSlidingMoves(const Board& board, int startSquare, std::vector<Move>& moves, int piece);
    void GenerateKingMoves(const Board& board, std::vector<Move>& moves);
    void GeneratePawnMoves(const Board& board, std::vector<Move>& moves);
    void GenerateKnightMoves(const Board& board, std::vector<Move>& moves);
};

#endif // MOVEGENERATOR_H
