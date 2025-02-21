#pragma once

#include <cstdint>
#include "Board.h"
#include "MoveGenerator.h"

class GameState {
public:
    enum class PlayerType {
        Human,
        AI
    };

    enum class Result {
        ONGOING,
        WHITE_WINS,
        BLACK_WINS,
        DRAW_STALEMATE,
        DRAW_INSUFFICIENT_MATERIAL,
        DRAW_REPETITION,
        DRAW_FIFTY_MOVE
    };

    // Constructor allows setting player types for both colors
    GameState(Board& board, PlayerType whitePlayerType = PlayerType::Human, PlayerType blackPlayerType = PlayerType::Human);

    bool IsWhiteTurn() const { return isWhiteTurn; }
    void SwitchTurn() { isWhiteTurn = !isWhiteTurn; }
    Result GetGameResult() const { return gameResult; }
    PlayerType GetCurrentPlayerType() const { return isWhiteTurn ? whitePlayerType : blackPlayerType; }

    // Returns true if move was legal and executed
    bool TryMakeMove(Move move, MoveGenerator& gene);

    // Check game ending conditions
    void UpdateGameState();

private:
    bool IsCheckmate();
    bool IsStalemate();
    bool HasInsufficientMaterial() const;
    bool IsThreefoldRepetition() const;
    bool IsFiftyMoveRule() const;

    Board& board;
    MoveGenerator moveGenerator;
    bool isWhiteTurn;
    Result gameResult;

    PlayerType whitePlayerType;
    PlayerType blackPlayerType;

    int halfMoveClock; 
    std::vector<uint64_t> positionHistory; 
};