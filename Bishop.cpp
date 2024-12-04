// Bishop.cpp
// This file provides the implementation for the Bishop class, which represents a bishop chess piece.

#include "Bishop.h"
#include "ChessGame.h"

// Constructor that sets the color of the bishop
Bishop::Bishop(Color pieceColor) : ChessPiece(pieceColor) {
    // Initialize the bishop with the given color
}

// Destructor, ensures proper cleanup for Bishop objects
Bishop::~Bishop() {
    // No specific resources to release for Bishop
}

// Implementation of the pure virtual function to get the symbol representing the piece
// Returns 'B' for a bishop
char Bishop::getSymbol() const {
    return 'B';
}
 // Returns 'Bishop'
string Bishop::getName() const {
    return "Bishop";
}

// Implementation of the pure virtual function to check if a move is valid for the bishop
// Bishops move diagonally any number of squares
bool Bishop::isValidMove(const Position& from, const Position& to, const ChessGame& game) const{
    // 'game' is currently unused for Bishop but included to maintain consistent interface.
    (void)game; 
    int rowDifference = abs(to.getRow() - from.getRow());
    int colDifference = abs(to.getCol() - from.getCol());

    // A valid bishop move must have equal row and column differences (move diagonally)
    return (rowDifference == colDifference);
}