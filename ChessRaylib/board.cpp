#include "Board.h"
#include "piece.h"

Board::Board(int boardArray[64]) {
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
            if ((x + y) % 2 == 0) {
                DrawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, LIGHTGRAY);
            }
            else {
                DrawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, DARKGRAY);
            }

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

int Board::TryToGetPieceUnderMouse(int mouseX, int mouseY){
    int tgtRow = mouseY / SQUARE_SIZE;
    int tgtCol = mouseX / SQUARE_SIZE;

    if (tgtRow >= 0 && tgtRow < BOARD_SIZE && tgtCol >= 0 && tgtCol < BOARD_SIZE) {
        int index = tgtRow * BOARD_SIZE + tgtCol;



        return board[index];;

        return -1; // Return -1 if mouse is outside board bounds
    }
}
