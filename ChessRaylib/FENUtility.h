#ifndef FENUTILITY_H
#define FENUTILITY_H

#include "raylib.h"
#include <string>

class FENUtility {
public:
	static void LoadPositionFromFEN(int board[64], const std::string& fen);

private:

	static int PieceFromChar(char c);
	static void ClearBoard(int board[64]);

};

#endif // FENUTILITY_H