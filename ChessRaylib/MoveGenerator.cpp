#include "MoveGenerator.h"
#include <iostream>

std::vector<Move> MoveGenerator::GenerateMoves(const Board& board, int color) {
    std::vector<Move> moves;
    CalculateNumSquaresToEdge();

    std::cout << "Generating moves for color: " << 
        (color == Piece::White ? "White" : "Black") << std::endl;

    // Generate all possible moves
    for (int startSquare = 0; startSquare < 64; startSquare++) {
        int piece = board[startSquare];
        
        // Skip empty squares and opponent's pieces
        if (piece == Piece::None || Piece::Color(piece) != color) {
            continue;
        }

        // Debug verification
        if (Piece::Color(piece) != color) {
            std::cout << "ERROR: Wrong color piece being processed!" << std::endl;
            continue;
        }

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

    // Filter out moves that would leave us in check
    std::vector<Move> legalMoves;
    int kingSquare = board.getKingPosition(color);
    
    for (const Move& move : moves) {
        // Verify the piece color matches the current turn
        int pieceColor = Piece::Color(board[move.StartingSquare]);
        if (pieceColor != color) {
            continue;  // Skip moves for pieces of the wrong color
        }

        // Create a temporary board to test the move
        Board tempBoard = board;
        tempBoard[move.TargetSquare] = tempBoard[move.StartingSquare];
        tempBoard[move.StartingSquare] = Piece::None;
        
        // Find the king's new position (in case this was a king move)
        int newKingSquare = Piece::IsType(board[move.StartingSquare], Piece::King) ? 
            move.TargetSquare : kingSquare;
            
        if (!IsSquareAttacked(tempBoard, newKingSquare, (color == Piece::White) ? Piece::Black : Piece::White)) {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}

void MoveGenerator::GenerateSlidingMoves(const Board& board, int startSquare, std::vector<Move>& moves, int pieceType) {
    // First verify there's actually a piece at the start square
    if (board[startSquare] == Piece::None) return;

    // Directions: North, South, West, East, NorthWest, SouthEast, NorthEast, SouthWest
    int DirectionOffsets[8] = { -8, 8, -1, 1, -9, 9, -7, 7 };

    int startDirIndex = 0;
    int endDirIndex = 8;

    if (Piece::IsType(pieceType, Piece::Bishop)) {
        startDirIndex = 4; // Start from diagonal directions
    }
    else if (Piece::IsType(pieceType, Piece::Rook)) {
        endDirIndex = 4; // Only use orthogonal directions
    }

    for (int directionIndex = startDirIndex; directionIndex < endDirIndex; directionIndex++) {
        for (int n = 1; n <= NumSquaresToEdge[startSquare][directionIndex]; n++) {
            int targetSquare = startSquare + DirectionOffsets[directionIndex] * n;
            int pieceOnTargetSquare = board[targetSquare];

            // If square is occupied by friendly piece, stop looking in this direction
            if (pieceOnTargetSquare != Piece::None && 
                Piece::Color(pieceOnTargetSquare) == Piece::Color(board[startSquare])) {
                break;
            }

            moves.emplace_back(startSquare, targetSquare);

            // If square is occupied by enemy piece, stop looking in this direction after capturing
            if (pieceOnTargetSquare != Piece::None) {
                break;
            }
        }
    }
}

void MoveGenerator::GenerateKingMoves(const Board& board, std::vector<Move>& moves) {
    int KingOffsets[8] = { -8, 8, -1, 1, -9, 9, -7, 7 };

    for (int startSquare = 0; startSquare < 64; startSquare++) {
        int piece = board[startSquare];
        if (!Piece::IsType(piece, Piece::King)) continue;

        int startFile = startSquare % 8;
        
        for (int offset : KingOffsets) {
            int targetSquare = startSquare + offset;
            if (targetSquare < 0 || targetSquare >= 64) continue;

            int targetFile = targetSquare % 8;
            // Prevent wrapping around board edges
            if (abs(targetFile - startFile) > 1) continue;

            int pieceOnTargetSquare = board[targetSquare];
            if (pieceOnTargetSquare == Piece::None || 
                Piece::Color(pieceOnTargetSquare) != Piece::Color(piece)) {
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
    for (int squareIndex = 0; squareIndex < 64; squareIndex++) {
        int file = squareIndex % 8;  // column (file) index
        int rank = squareIndex / 8;  // row (rank) index

        int numNorth = rank;  // Distance to north edge (top)
        int numSouth = 7 - rank;  // Distance to south edge (bottom)
        int numWest = file;  // Distance to west edge (left)
        int numEast = 7 - file;  // Distance to east edge (right)

        // Store distances in the array (matching DirectionOffsets order)
        NumSquaresToEdge[squareIndex][0] = numNorth;  // North
        NumSquaresToEdge[squareIndex][1] = numSouth;  // South
        NumSquaresToEdge[squareIndex][2] = numWest;   // West
        NumSquaresToEdge[squareIndex][3] = numEast;   // East
        NumSquaresToEdge[squareIndex][4] = std::min(numNorth, numWest);  // Northwest
        NumSquaresToEdge[squareIndex][5] = std::min(numSouth, numEast);  // Southeast
        NumSquaresToEdge[squareIndex][6] = std::min(numNorth, numEast);  // Northeast
        NumSquaresToEdge[squareIndex][7] = std::min(numSouth, numWest);  // Southwest
    }
}

bool MoveGenerator::IsSquareAttacked(const Board& board, int square, int attackingColor) {
    // Check for attacking pawns
    int pawnDirection = (attackingColor == Piece::White) ? -1 : 1;
    int file = square % 8;
    
    // Check left capture
    if (file > 0) {
        int attackSquare = square + (pawnDirection * 8) - 1;
        if (attackSquare >= 0 && attackSquare < 64) {
            int piece = board[attackSquare];
            if (Piece::IsType(piece, Piece::Pawn) && Piece::Color(piece) == attackingColor) {
                return true;
            }
        }
    }
    
    // Check right capture
    if (file < 7) {
        int attackSquare = square + (pawnDirection * 8) + 1;
        if (attackSquare >= 0 && attackSquare < 64) {
            int piece = board[attackSquare];
            if (Piece::IsType(piece, Piece::Pawn) && Piece::Color(piece) == attackingColor) {
                return true;
            }
        }
    }

    // Check for attacking knights
    int KnightOffsets[8] = { 17, 15, 10, 6, -6, -10, -15, -17 };
    for (int offset : KnightOffsets) {
        int targetSquare = square + offset;
        if (targetSquare >= 0 && targetSquare < 64) {
            int piece = board[targetSquare];
            if (Piece::IsType(piece, Piece::Knight) && Piece::Color(piece) == attackingColor) {
                return true;
            }
        }
    }

    // Check for attacking sliding pieces (Queen, Rook, Bishop)
    int DirectionOffsets[8] = { -8, 8, -1, 1, -9, 9, -7, 7 };
    for (int directionIndex = 0; directionIndex < 8; directionIndex++) {
        for (int n = 1; n <= NumSquaresToEdge[square][directionIndex]; n++) {
            int targetSquare = square + DirectionOffsets[directionIndex] * n;
            int piece = board[targetSquare];
            
            if (piece != Piece::None) {
                if (Piece::Color(piece) == attackingColor) {
                    // Check if this piece can attack along this direction
                    bool isDiagonal = directionIndex >= 4;
                    if ((Piece::IsType(piece, Piece::Queen)) ||
                        (Piece::IsType(piece, Piece::Rook) && !isDiagonal) ||
                        (Piece::IsType(piece, Piece::Bishop) && isDiagonal)) {
                        return true;
                    }
                }
                break;
            }
        }
    }

    // Check for attacking king
    int KingOffsets[8] = { -8, 8, -1, 1, -9, 9, -7, 7 };
    for (int offset : KingOffsets) {
        int targetSquare = square + offset;
        if (targetSquare >= 0 && targetSquare < 64) {
            int piece = board[targetSquare];
            if (Piece::IsType(piece, Piece::King) && Piece::Color(piece) == attackingColor) {
                return true;
            }
        }
    }

    return false;
}





