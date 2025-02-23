#include "GameState.h"
#include <iostream>

GameState::GameState(Board& board, PlayerType whitePlayerType, PlayerType blackPlayerType)
    : board(board)
    , isWhiteTurn(true)
    , gameResult(Result::ONGOING)
    , whitePlayerType(whitePlayerType)
    , blackPlayerType(blackPlayerType)
    , halfMoveClock(0)
{
}

bool GameState::TryMakeMove(Move move, MoveGenerator& gene) {
    int currentColor = isWhiteTurn ? Piece::White : Piece::Black;
    std::vector<Move> legalMoves = gene.GenerateMoves(board, currentColor);

    // Check if move is legal
    bool isLegal = false;
    for (const Move& legalMove : legalMoves) {
        if (move.StartingSquare == legalMove.StartingSquare &&
            move.TargetSquare == legalMove.TargetSquare) {
            isLegal = true;
            break;
        }
    }

    if (!isLegal) return false;

    // Update fifty move rule counter
    if (Piece::IsType(board[move.StartingSquare], Piece::Pawn) ||
        board[move.TargetSquare] != Piece::None) {
        halfMoveClock = 0;
    }
    else {
        halfMoveClock++;
    }

    // Make the move
    board.MakeMove(move);

    // Switch turns
    SwitchTurn();

    // Update game state
    UpdateGameState();

    return true;
}

void GameState::UpdateGameState() {
    if (IsCheckmate()) {
        gameResult = isWhiteTurn ? Result::BLACK_WINS : Result::WHITE_WINS;
    }
    else if (IsStalemate()) {
        gameResult = Result::DRAW_STALEMATE;
    }
    else if (HasInsufficientMaterial()) {
        gameResult = Result::DRAW_INSUFFICIENT_MATERIAL;
    }
    else if (IsThreefoldRepetition()) {
        gameResult = Result::DRAW_REPETITION;
    }
    else if (IsFiftyMoveRule()) {
        gameResult = Result::DRAW_FIFTY_MOVE;
    }
}

bool GameState::IsCheckmate() {
    int currentColor = isWhiteTurn ? Piece::White : Piece::Black;
    int kingSquare = board.getKingPosition(currentColor);
    
    // First check if we're in check
    MoveGenerator moveGenerator;
    bool isInCheck = moveGenerator.IsSquareAttacked(board, kingSquare, 
        currentColor == Piece::White ? Piece::Black : Piece::White);
    
    if (!isInCheck) {
        return false;
    }

    std::vector<Move> legalMoves = moveGenerator.GenerateMoves(board, currentColor);

    return legalMoves.empty();
}

bool GameState::IsStalemate() {
    int currentColor = isWhiteTurn ? Piece::White : Piece::Black;
    int kingSquare = board.getKingPosition(currentColor);
    
    // First verify we're not in check
    MoveGenerator moveGenerator;
    bool isInCheck = moveGenerator.IsSquareAttacked(board, kingSquare, 
        currentColor == Piece::White ? Piece::Black : Piece::White);
    
    if (isInCheck) {
        return false;
    }
    
    // If we're not in check but have no legal moves, it's stalemate
    std::vector<Move> legalMoves = moveGenerator.GenerateMoves(board, currentColor);
    return legalMoves.empty();
}

bool GameState::HasInsufficientMaterial() const {
    return false;
}
bool GameState::IsThreefoldRepetition() const {
    return false;
}
bool GameState::IsFiftyMoveRule() const {
    return false;
}