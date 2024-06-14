#include <iostream>
#include "raylib.h"
#include "board.h"
#include <string>
#include "FENUtility.h"
#include "piece.h"

void HandleInput(Board& board);
void HandlePieceSelection(Board& board);

int main(void)
{
    const int screenWidth = Board::BOARD_SIZE * Board::SQUARE_SIZE;
    const int screenHeight = Board::BOARD_SIZE * Board::SQUARE_SIZE;

    const std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    int boardArray[64];
    FENUtility::LoadPositionFromFEN(boardArray, startFen);

    Board board(boardArray);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(30);

    // Main game loop
    while (!WindowShouldClose())
    {
        HandleInput(board);

        BeginDrawing();
        ClearBackground(DARKGRAY);
        board.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void HandleInput(Board& board)
{
    if (IsMouseButtonPressed(0))
    {
        HandlePieceSelection(board);
    }

    if (IsMouseButtonPressed(1))
    {
        board.SetSelectedPiece(-1);
    }
}

void HandlePieceSelection(Board& board)
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int index = board.TryToGetPieceUnderMouse(mouseX, mouseY);

    if (index != -1) // Assuming -1 is returned if no piece is found
    {
       
        int piece = board[index];
        if (Piece::PieceType(piece) == Piece::None) return;
        std::cout << "Piece selected at index: " << index << std::endl;
        board.SetSelectedPiece(index);
    }
}
