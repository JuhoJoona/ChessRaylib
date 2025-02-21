#include <iostream>
#include "raylib.h"
#include "board.h"
#include <string>
#include "FENUtility.h"
#include "piece.h"
#include "TextureHandler.h"
#include "MoveGenerator.h"
#include "GameState.h"


void HandleInput(Board& board, GameState& state);
void HandlePieceSelection(Board& board, GameState& state);
void CancelSelection(Board& board);
void TryToMakeMove(Board& board, int square, GameState& state);

int main(void)
{
    const int screenWidth = Board::BOARD_SIZE * Board::SQUARE_SIZE;
    const int screenHeight = Board::BOARD_SIZE * Board::SQUARE_SIZE;

    const std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    int boardArray[64];
    FENUtility::LoadPositionFromFEN(boardArray, startFen);

    Board board(boardArray);

    GameState gameState(board, GameState::PlayerType::Human, GameState::PlayerType::Human);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");



    TextureHandler& handler = TextureHandler::getInstance();

    handler.LoadTextures();
   

    SetTargetFPS(30);

    // Main game loop
    while (!WindowShouldClose())
    {
        HandleInput(board, gameState);

        BeginDrawing();

        ClearBackground(DARKGRAY);

        board.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void HandleInput(Board& board, GameState& state)
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

            TryToMakeMove(board, square, state);
        }
        else
        {
            HandlePieceSelection(board, state);
        }
        
    }

    if (IsMouseButtonPressed(1))
    {
        CancelSelection(board);
    }
}

void HandlePieceSelection(Board& board, GameState& state) {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int index = board.TryToGetSquareUnderMouse(mouseX, mouseY);

    if (index != -1) {
        int piece = board[index];
        if (piece == Piece::None) return;

        // Only allow selecting pieces of current player's color

        bool isWhitePiece = Piece::Color(piece) == Piece::White;

        if (isWhitePiece != state.IsWhiteTurn()) return;
;
        board.SetSelectedPiece(piece, index);
        std::cout << index << std::endl;
    }
}

void CancelSelection(Board& board)
{
    board.SetSelectedPiece(-1, -1);
}


void TryToMakeMove(Board& board, int square, GameState& state) {
    MoveGenerator moveGene;
    // Get the color of the selected piece
    int selectedPieceColor = Piece::Color(board.selectedPiece);
    // Generate moves only for pieces of the selected color
    std::vector<Move> moves = moveGene.GenerateMoves(board, selectedPieceColor);

    int startSquare = board.selectedPieceIndex;
    int targetSquare = square;

    for (const Move& move : moves) {
        if (move.StartingSquare == startSquare && move.TargetSquare == targetSquare) {
            state.TryMakeMove(move, moveGene);
            return;
        }
    }
 
    // If no valid move was found, deselect the piece
    CancelSelection(board);
}
