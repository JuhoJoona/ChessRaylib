#include "Piece.h"

int Piece::Color(int piece) {
    return piece & (blackMask | whiteMask);
}

int Piece::PieceType(int piece) {
    return piece & typeMask;
}

bool Piece::IsRookOrQueen(int piece) {
    int pieceType = PieceType(piece);
    return pieceType == Rook || pieceType == Queen;
}

bool Piece::IsSlidingPiece(int piece) {
    int pieceType = PieceType(piece);
    return pieceType == Bishop || pieceType == Rook || pieceType == Queen;
}
