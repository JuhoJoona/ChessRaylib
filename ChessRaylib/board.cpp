#include "Board.h"
#include "piece.h"
#include "TextureHandler.h"
#include "raylib.h"

Board::Board(int boardArray[64]) : selectedPieceIndex(-1) {
    for (int i = 0; i < 64; i++) {
        board[i] = boardArray[i];
    }
}

void Board::Draw() const {
    // Define the size of each piece
    const float PIECE_SIZE = SQUARE_SIZE * 0.8f; // Adjust the scaling factor as needed

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            int index = y * BOARD_SIZE + x;
            int value = board[index];

            // Draw square
            Color squareColor = ((x + y) % 2 == 0) ? LIGHTGRAY : DARKGRAY;

            // Highlight legal moves
            if (std::find(legalMoves.begin(), legalMoves.end(), index) != legalMoves.end()) {
                squareColor = YELLOW; 
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

std::vector<int> Board::CalculateLegalMoves(int pieceIndex) {
    // Dummy implementation, replace with actual move calculation logic
    std::vector<int> moves;
    int row = pieceIndex / BOARD_SIZE;
    int col = pieceIndex % BOARD_SIZE;

    // Example: Add adjacent squares as legal moves (for demonstration)
    if (row > 0) moves.push_back((row - 1) * BOARD_SIZE + col); // Up
    if (row < BOARD_SIZE - 1) moves.push_back((row + 1) * BOARD_SIZE + col); // Down
    if (col > 0) moves.push_back(row * BOARD_SIZE + (col - 1)); // Left
    if (col < BOARD_SIZE - 1) moves.push_back(row * BOARD_SIZE + (col + 1)); // Right

    return moves;
}

int Board::TryToGetPieceUnderMouse(int mouseX, int mouseY) {
    int tgtRow = mouseY / SQUARE_SIZE;
    int tgtCol = mouseX / SQUARE_SIZE;

    if (tgtRow >= 0 && tgtRow < BOARD_SIZE && tgtCol >= 0 && tgtCol < BOARD_SIZE) {
        int index = tgtRow * BOARD_SIZE + tgtCol;
        return index;
    }
    return -1; // Return -1 if mouse is outside board bounds
}

void Board::SetSelectedPiece(int index) {
    selectedPieceIndex = index;
    if (index != -1) {
        legalMoves = CalculateLegalMoves(index);
    }
    else {
        legalMoves.clear();
    }
}

// Operator[] to access board elements
int Board::operator[](int index) const {
    return board[index];
}

int& Board::operator[](int index) {
    return board[index];
}
