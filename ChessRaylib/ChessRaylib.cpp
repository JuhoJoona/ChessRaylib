#include <iostream>
#include "raylib.h"
#include "board.h"
#include <string>
#include "FENUtility.h"
#include "piece.h"
#include "TextureHandler.h"
#include "MoveGenerator.h"

void HandleInput(Board& board);
void HandlePieceSelection(Board& board);
void CancelSelection(Board& board);
void TryToMakeMove(Board& board, int square);

int main(void)
{
    const int screenWidth = Board::BOARD_SIZE * Board::SQUARE_SIZE;
    const int screenHeight = Board::BOARD_SIZE * Board::SQUARE_SIZE;

    const std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    int boardArray[64];
    FENUtility::LoadPositionFromFEN(boardArray, startFen);

    Board board(boardArray);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");



    TextureHandler& handler = TextureHandler::getInstance();

    handler.LoadTextures();
   

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
        if (board.selectedPiece != -1)
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            int square = board.TryToGetSquareUnderMouse(mouseX, mouseY);

            if (board.selectedPieceIndex == square)
            {
                CancelSelection(board);
                return;
            }

            std::cout << "making a move " << std::endl;
            TryToMakeMove(board, square);
        }
        else
        {
            HandlePieceSelection(board);
        }
        
    }

    if (IsMouseButtonPressed(1))
    {
        CancelSelection(board);
    }
}

void HandlePieceSelection(Board& board) {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int index = board.TryToGetSquareUnderMouse(mouseX, mouseY);

    if (index != -1) {
        int piece = board[index];
        if (Piece::PieceType(piece) == Piece::None) return;

        std::cout << "Piece selected: " << piece << std::endl;
        board.SetSelectedPiece(piece, index);
    }
}

void CancelSelection(Board& board)
{
    board.SetSelectedPiece(-1, -1);
}


void TryToMakeMove(Board& board, int square) {
    MoveGenerator moveGene;
    std::vector<Move> moves = moveGene.GenerateMoves(board);

    for (const auto& move : moves) {
        //std::cout << "Move from (" << move.StartingSquare << ") to (" << move.TargetSquare << ")" << std::endl;
    }

    

    int startSquare = board.selectedPieceIndex;
    int targetSquare = square;

    for (const Move& move : moves) {
        if (move.StartingSquare == startSquare && move.TargetSquare == targetSquare) {
            board.MakeMove(move);
            return;
        }
    }
 
    // If no valid move was found, deselect the piece
    CancelSelection(board);
}
