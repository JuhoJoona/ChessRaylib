#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include "raylib.h"
#include "piece.h" // Assuming Piece enum is defined here or included properly

class TextureHandler {
public:
    static TextureHandler& getInstance() {
        static TextureHandler instance;
        return instance;
    }

    void LoadTextures();
    Texture2D TextureByPiece(int type);

private:
    TextureHandler(); // Private constructor to enforce singleton pattern
    ~TextureHandler(); // Private destructor to prevent accidental deletion
    TextureHandler(const TextureHandler&) = delete; // Delete copy constructor
    TextureHandler& operator=(const TextureHandler&) = delete; // Delete assignment operator

    // Texture variables
    Texture2D King;
    Texture2D Pawn;
    Texture2D Knight;
    Texture2D Bishop;
    Texture2D Rook;
    Texture2D Queen;

    // File paths for textures
    const char* KingPath = "Textures/w_king_1x_ns.png";
    const char* PawnPath = "Textures/w_pawn_1x_ns.png";
    const char* KnightPath = "Textures/w_rook_1x_ns.png";
    const char* BishopPath = "Textures/w_bishop_1x_ns.png";
    const char* RookPath = "Textures/w_knight_1x_ns.png";
    const char* QueenPath = "Textures/w_queen_1x_ns.png";
};

#endif // TEXTUREHANDLER_H
