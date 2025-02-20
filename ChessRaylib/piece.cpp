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

bool Piece::IsType(int piece, int PieceToCompare)
{
    return PieceType(piece) == PieceType(PieceToCompare);
}


bool Piece::IsColor(int piece, int color)
{
    int pieceColor = Piece::Color(piece);

    return pieceColor == color;
}

bool Piece::HasMoved(int piece)
{
    return piece & Piece::hasMovedMask;
}

bool Piece::IsChecked(int piece) {

    return piece & Piece::isCheckedMask;

}
int Piece::SetHasMoved(int piece) {

    return piece | hasMovedMask;

}

int Piece::SetChecked(int piece, bool checked) {
    if (checked) {
        return piece | isCheckedMask;
    }
    else {
        return piece & ~isCheckedMask;
    }
}