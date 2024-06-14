#include "TextureHandler.h"

TextureHandler::TextureHandler() {
    // Initialize your member variables if needed
}

void TextureHandler::LoadTextures() {
    // Load King texture
    Image kingImage = LoadImage(KingPath);
    King = LoadTextureFromImage(kingImage);
    UnloadImage(kingImage);

    // Load Pawn texture
    Image pawnImage = LoadImage(PawnPath);
    Pawn = LoadTextureFromImage(pawnImage);
    UnloadImage(pawnImage);

    // Load Knight texture
    Image knightImage = LoadImage(KnightPath);
    Knight = LoadTextureFromImage(knightImage);
    UnloadImage(knightImage);

    // Load Bishop texture
    Image bishopImage = LoadImage(BishopPath);
    Bishop = LoadTextureFromImage(bishopImage);
    UnloadImage(bishopImage);

    // Load Rook texture
    Image rookImage = LoadImage(RookPath);
    Rook = LoadTextureFromImage(rookImage);
    UnloadImage(rookImage);

    // Load Queen texture
    Image queenImage = LoadImage(QueenPath);
    Queen = LoadTextureFromImage(queenImage);
    UnloadImage(queenImage);
}

TextureHandler::~TextureHandler() {
    // Cleanup any resources if needed
    // For example, unload textures
    UnloadTexture(King);
    UnloadTexture(Pawn);
    UnloadTexture(Knight);
    UnloadTexture(Bishop);
    UnloadTexture(Rook);
    UnloadTexture(Queen);
}

Texture2D TextureHandler::TextureByPiece(int type) {
    switch (type) {
    case Piece::Pawn:
        return Pawn;
    case Piece::Knight:
        return Knight;
    case Piece::Bishop:
        return Bishop;
    case Piece::Rook:
        return Rook;
    case Piece::King:
        return King;
    case Piece::Queen:
        return Queen;
    default:
        // Handle invalid type gracefully
        // For example, return a default texture or throw an exception
        return King; // Replace with appropriate default behavior
    }
}
