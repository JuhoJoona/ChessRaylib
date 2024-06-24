#include "Board.h"
#include "piece.h"
#include "TextureHandler.h"
#include "raylib.h"
#include <iostream>
#include "MoveGenerator.h"

Board::Board(int boardArray[64]) : selectedPiece(-1) {
    for (int i = 0; i < 64; i++) {
        board[i] = boardArray[i];
    }
}

void Board::Draw() const {
    const float PIECE_SIZE = SQUARE_SIZE * 0.8f;

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            int index = y * BOARD_SIZE + x;
            int value = board[index];

            Color squareColor = ((x + y) % 2 == 0) ? LIGHTGRAY : DARKGRAY;

            if (index == selectedPieceIndex) {
                squareColor = YELLOW;
            }

            //higlight legalmoves
            if (selectedPieceIndex != -1) {

                MoveGenerator moveGene;

                std::vector<Move> legalMoves = moveGene.GenerateMoves(*this); // Generate legal moves

                for (const Move& move : legalMoves) {
                    if (move.StartingSquare == selectedPieceIndex && move.TargetSquare == index) {
                        squareColor = GREEN; // Highlight legal move square
                        break;
                    }
                }
            }


            DrawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, squareColor);

            if (value != 0) {
                int pieceType = Piece::PieceType(value);
                int pieceColor = Piece::Color(value);

                Color color = (pieceColor == Piece::White) ? WHITE : BLACK;

                TextureHandler& handler = TextureHandler::getInstance();

                Rectangle destRec = {
                    x * SQUARE_SIZE + (SQUARE_SIZE - PIECE_SIZE) / 2,
                    y * SQUARE_SIZE + (SQUARE_SIZE - PIECE_SIZE) / 2,
                    PIECE_SIZE,
                    PIECE_SIZE
                };

                DrawTexturePro(handler.TextureByPiece(pieceType),
                    Rectangle{ 0.0f, 0.0f, static_cast<float>(handler.TextureByPiece(pieceType).width), static_cast<float>(handler.TextureByPiece(pieceType).height) },
                    destRec,
                    Vector2{ 0.0f, 0.0f },
                    0.0f,
                    color);
            }
        }
    }
}


int Board::FindPieceIndex(int piece) const {
    for (int i = 0; i < 64; i++) {
        if (Piece::PieceType(board[i]) == Piece::PieceType(piece) &&
            Piece::Color(board[i]) == Piece::Color(piece)) {
            return i;
        }
    }
    return -1; // Return -1 if the piece is not found
}

int Board::TryToGetSquareUnderMouse(int mouseX, int mouseY) {
    int tgtRow = mouseY / SQUARE_SIZE;
    int tgtCol = mouseX / SQUARE_SIZE;

    if (tgtRow >= 0 && tgtRow < BOARD_SIZE && tgtCol >= 0 && tgtCol < BOARD_SIZE) {
        int index = tgtRow * BOARD_SIZE + tgtCol;
        return index;
    }
    return -1; // Return -1 if mouse is outside board bounds
}

void Board::SetSelectedPiece(int piece, int pieceIndex) {
    selectedPiece = piece;
    selectedPieceIndex = pieceIndex;

}

void Board::MakeMove(Move move) {
    // Move the piece
    board[move.TargetSquare] = board[move.StartingSquare];
    // Clear the source square
    board[move.StartingSquare] = 0;

    // Deselect the piece
    SetSelectedPiece(-1, -1);
}

// Operator[] to access board elements
int Board::operator[](int index) const {
    return board[index];
}

int& Board::operator[](int index) {
    return board[index];
}
