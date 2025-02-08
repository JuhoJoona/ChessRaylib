# Chess Game with Raylib

A chess implementation using C++ and the Raylib graphics library.

## Project Structure

```
ChessRaylib/
├── ChessRaylib.cpp      # Main game loop and input handling
├── board.h/cpp          # Chess board representation and game state
├── piece.h/cpp          # Piece definitions and utility functions
├── Move.h               # Move representation
├── MoveGenerator.h/cpp  # Legal move generation
├── FENUtility.h/cpp     # FEN string parsing for board positions
└── TextureHandler.h/cpp # Piece texture loading and management
```

## Core Components

### Board (board.h/cpp)
- Represents the 8x8 chess board
- Stores piece positions using an integer array
- Handles piece selection and movement
- Manages game state (turns, check, checkmate)
- Provides methods for move validation

### Piece (piece.h/cpp)
- Defines piece types and colors
- Uses bit flags for piece properties:
  - Bits 0-2: Piece type (King=1, Pawn=2, Knight=3, Bishop=5, Rook=6, Queen=7)
  - Bit 3: White (8)
  - Bit 4: Black (16)
- Provides utility methods for piece manipulation

### Move Generator (MoveGenerator.h/cpp)
- Generates legal moves for all pieces
- Handles special moves:
  - Castling
  - En passant
  - Pawn promotion
- Validates moves against check

### FEN Utility (FENUtility.h/cpp)
- Parses Forsyth–Edwards Notation (FEN) strings
- Loads chess positions from FEN notation
- Default starting position: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

### Texture Handler (TextureHandler.h/cpp)
- Singleton class for managing piece textures
- Loads and stores piece images
- Provides texture access for rendering

## Game Flow

1. **Game initialization:**
   - Board setup from FEN string
   - Texture loading
   - Window creation

2. **Main game loop:**
   - Handle input (mouse clicks)
   - Update game state
   - Render board and pieces

3. **Move execution:**
   - Piece selection
   - Move validation
   - State updates (turns, check, etc.)
   - Board redraw

## Technical Details

### Piece Representation
Pieces are stored as integers with bit flags:

```
// Example: White Queen = 7 | 8 = 15
// Binary: 0000 1111
// ||||-||||
// ||||Type (7 = Queen)
// |||White (8)
// ||Black (0)
```

### Board Representation
- 64-square array (0-63)
- Index calculation: `rank * 8 + file`
- Zero-based indexing (0,0 is top-left)

### Move Validation
1. Check if piece belongs to current player
2. Generate legal moves for selected piece
3. Verify move doesn't expose king to check
4. Handle special cases (castling, en passant)

## Dependencies

- [Raylib](https://www.raylib.com/) - Graphics library
- C++11 or higher
- CMake for building

## Building and Running

```bash
mkdir build
cd build
cmake ..
make
./ChessRaylib
```

## Controls

- **Left Click:** Select piece/Make move
- **Right Click:** Deselect piece

## Implementation Status

### Completed Features
- Basic board representation
- Piece movement
- Move generation for all pieces
- FEN position loading
- Basic GUI with Raylib

### TODO
- [ ] Check detection
- [ ] Checkmate detection
- [ ] Turn management
- [ ] Pawn promotion
- [ ] Castling
- [ ] En passant
- [ ] Move validation against check
- [ ] Game state saving/loading
- [ ] Move history
- [ ] Draw detection (stalemate, insufficient material, etc.)



