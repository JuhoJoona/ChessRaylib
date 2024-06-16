#include "MoveGenerator.h"
#include <iostream>

std::vector<Move> MoveGenerator::GenerateMoves(const Board& board) {
    std::vector<Move> moves;

    CalculateNumSquaresToEdge();

    for (int startSquare = 0; startSquare < 64; startSquare++) {
        int piece = board[startSquare];


        if (Piece::IsType(piece, Piece::Bishop) || Piece::IsType(piece, Piece::Rook) || Piece::IsType(piece, Piece::Queen)) {
            GenerateSlidingMoves(board, startSquare, moves, piece);
        }
        else if (Piece::IsType(piece, Piece::King)) {
            GenerateKingMoves(board, moves);
        }
        else if (Piece::IsType(piece, Piece::Pawn)) {
            GeneratePawnMoves(board, moves);
        }
        else if (Piece::IsType(piece, Piece::Knight)) {
            GenerateKnightMoves(board, moves);
        }
    }

    return moves;
}




void MoveGenerator::GenerateSlidingMoves(const Board& board, int startSquare, std::vector<Move>& moves, int pieceType) {

    int DirectionOffsets[8] = { 8, -8, -1, 1, 7, -7, 9, -9 };

    int startDirIndex = 0;
    int endDirIndex = 8;

    if (Piece::IsType(pieceType, Piece::Bishop)) {
        startDirIndex = 4; 
    }
    else if (Piece::IsType(pieceType, Piece::Rook)) {
        endDirIndex = 4; 
    }

    for (int directionIndex = startDirIndex; directionIndex < endDirIndex; directionIndex++) {

        for (int n = 1; n <= NumSquaresToEdge[startSquare][directionIndex]; n++) {
            int targetSquare = startSquare + DirectionOffsets[directionIndex] * n;


            if (targetSquare < 0 || targetSquare >= 64) {
                break; 
            }

            int pieceOnTargetSquare = board[targetSquare];

            std::cout << pieceOnTargetSquare << std::endl;

            if (pieceOnTargetSquare == Piece::None) {
                
                moves.emplace_back(startSquare, targetSquare);
            }
            else {

                if (Piece::Color(pieceOnTargetSquare) != Piece::Color(pieceType)) {
                    moves.emplace_back(startSquare, targetSquare);
                }
                break; 
            }
        }
    }
}





void MoveGenerator::GenerateKingMoves(const Board& board, std::vector<Move>& moves) {

    int KingOffsets[8] = { 8, -8, 1, -1, 9, -9, 7, -7 };


    for (int startSquare = 0; startSquare < 64; startSquare++) {
        int piece = board[startSquare];

        if (!Piece::IsType(piece, Piece::King)) continue;

        for (int offset : KingOffsets) {
            int targetSquare = startSquare + offset;

            if (targetSquare < 0 || targetSquare >= 64) continue;


            int pieceOnTargetSquare = board[targetSquare];

            if (pieceOnTargetSquare == Piece::None || Piece::Color(pieceOnTargetSquare) != Piece::Color(piece)) {
                moves.emplace_back(startSquare, targetSquare);
            }
        }
    }


}

void MoveGenerator::GeneratePawnMoves(const Board& board, std::vector<Move>& moves) {
    for (int square = 0; square < 64; square++) {
        int piece = board[square];

        if (!Piece::IsType(piece, Piece::Pawn)) continue;

        if (Piece::IsColor(piece, Piece::White)) {
            int forwardSquare = square - 8;

            // Single square move
            if (board[forwardSquare] == Piece::None) {
                moves.emplace_back(square, forwardSquare);

                // Double square move from starting position
                if (square >= 48 && square <= 55) { // 2nd rank for white pawns
                    int doubleForwardSquare = square - 16;
                    if (board[doubleForwardSquare] == Piece::None) {
                        moves.emplace_back(square, doubleForwardSquare);
                    }
                }
            }

            // Capture moves
            if (square % 8 != 0) { // Not on the left edge
                int captureLeft = square - 9;
                if (captureLeft >= 0 && Piece::IsColor(board[captureLeft], Piece::Black)) {
                    moves.emplace_back(square, captureLeft);
                }
            }
            if (square % 8 != 7) { // Not on the right edge
                int captureRight = square - 7;
                if (captureRight >= 0 && Piece::IsColor(board[captureRight], Piece::Black)) {
                    moves.emplace_back(square, captureRight);
                }
            }
        }
        else {
            int forwardSquare = square + 8;

            // Single square move
            if (board[forwardSquare] == Piece::None) {
                moves.emplace_back(square, forwardSquare);

                // Double square move from starting position
                if (square >= 8 && square <= 15) { // 7th rank for black pawns
                    int doubleForwardSquare = square + 16;
                    if (board[doubleForwardSquare] == Piece::None) {
                        moves.emplace_back(square, doubleForwardSquare);
                    }
                }
            }

            // Capture moves
            if (square % 8 != 0) { // Not on the left edge
                int captureLeft = square + 7;
                if (captureLeft < 64 && Piece::IsColor(board[captureLeft], Piece::White)) {
                    moves.emplace_back(square, captureLeft);
                }
            }
            if (square % 8 != 7) { // Not on the right edge
                int captureRight = square + 9;
                if (captureRight < 64 && Piece::IsColor(board[captureRight], Piece::White)) {
                    moves.emplace_back(square, captureRight);
                }
            }
        }
    }
}


void MoveGenerator::GenerateKnightMoves(const Board& board, std::vector<Move>& moves) {
    int KnightOffsets[8] = { 17, 15, 10, 6, -6, -10, -15, -17 };

    for (int startSquare = 0; startSquare < 64; startSquare++) {
        int piece = board[startSquare];

        if (!Piece::IsType(piece, Piece::Knight)) continue;

        for (int offset : KnightOffsets) {
            int targetSquare = startSquare + offset;

            if (targetSquare < 0 || targetSquare >= 64) continue;

            int startFile = startSquare % 8;
            int startRank = startSquare / 8;
            int targetFile = targetSquare % 8;
            int targetRank = targetSquare / 8;

            if ((abs(targetFile - startFile) == 2 && abs(targetRank - startRank) == 1) ||
                (abs(targetFile - startFile) == 1 && abs(targetRank - startRank) == 2)) {

                int pieceOnTargetSquare = board[targetSquare];

                if (pieceOnTargetSquare == Piece::None || Piece::Color(pieceOnTargetSquare) != Piece::Color(piece)) {
                    moves.emplace_back(startSquare, targetSquare);
                }
            }
        }
    }
}

void MoveGenerator::CalculateNumSquaresToEdge() {
    for (int file = 0; file < 8; file++) {
        for (int rank = 0; rank < 8; rank++) {
            int numNorth = 7 - rank;
            int numSouth = rank;
            int numWest = file;
            int numEast = 7 - file;

            int squareIndex = rank * 8 + file;

            NumSquaresToEdge[squareIndex][0] = numSouth;
            NumSquaresToEdge[squareIndex][1] = numWest;
            NumSquaresToEdge[squareIndex][2] = numNorth;
            NumSquaresToEdge[squareIndex][3] = numEast;
            NumSquaresToEdge[squareIndex][4] = std::min(numNorth, numWest);
            NumSquaresToEdge[squareIndex][5] = std::min(numSouth, numEast);
            NumSquaresToEdge[squareIndex][6] = std::min(numNorth, numEast);
            NumSquaresToEdge[squareIndex][7] = std::min(numSouth, numWest);
        }
    }
}

