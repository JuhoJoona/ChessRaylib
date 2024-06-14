#include "Board.h"
#include "piece.h"

Board::Board(int boardArray[64]) : selectedPieceIndex(-1) {
    for (int i = 0; i < 64; i++) {
        board[i] = boardArray[i];
    }
}

void Board::Draw() const {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            int index = y * BOARD_SIZE + x;
            int value = board[index];

            // Draw square
            Color squareColor = ((x + y) % 2 == 0) ? LIGHTGRAY : DARKGRAY;

            // Highlight legal moves
            if (std::find(legalMoves.begin(), legalMoves.end(), index) != legalMoves.end()) {
                squareColor = YELLOW; // Highlight color for legal moves
            }

            DrawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, squareColor);

            if (value != 0) {
                int pieceType = Piece::PieceType(value);
                int pieceColor = Piece::Color(value);

                // Determine piece color
                Color color = (pieceColor == Piece::White) ? WHITE : BLACK;

                // Draw a simple circle as a placeholder for the piece
                DrawCircle((x * SQUARE_SIZE) + SQUARE_SIZE / 2, (y * SQUARE_SIZE) + SQUARE_SIZE / 2, SQUARE_SIZE / 3, color);
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


