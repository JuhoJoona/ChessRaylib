#include "FENUtility.h"
#include <sstream>   // Include the sstream header for std::istringstream
#include <cctype>    // Include the cctype header for std::isdigit
#include "piece.h"

void FENUtility::LoadPositionFromFEN(int board[64], const std::string& fen) {
    ClearBoard(board);
    std::istringstream iss(fen);
    std::string boardPart;
    std::getline(iss, boardPart, ' ');

    int square = 0;
    for (char c : boardPart) {
        if (std::isdigit(c)) {
            square += c - '0';
        }
        else if (c == '/') {
            continue;
        }
        else {
            board[square] = PieceFromChar(c);
            square++;
        }
    }
}

int FENUtility::PieceFromChar(char c) {
    switch (c) {
    case 'r': return Piece::Rook | Piece::Black;
    case 'n': return Piece::Knight | Piece::Black;
    case 'b': return Piece::Bishop | Piece::Black;
    case 'q': return Piece::Queen | Piece::Black;
    case 'k': return Piece::King | Piece::Black;
    case 'p': return Piece::Pawn | Piece::Black;
    case 'R': return Piece::Rook | Piece::White;
    case 'N': return Piece::Knight | Piece::White;
    case 'B': return Piece::Bishop | Piece::White;
    case 'Q': return Piece::Queen | Piece::White;
    case 'K': return Piece::King | Piece::White;
    case 'P': return Piece::Pawn | Piece::White;
    default: return Piece::None;
    }
}

void FENUtility::ClearBoard(int board[64]) {
    for (int i = 0; i < 64; i++) {
        board[i] = Piece::None;
    }
}