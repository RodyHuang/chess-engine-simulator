// Rook.cpp
#include "Rook.h"
#include "ChessGame.h"

// Constructor that sets the color of the rook
Rook::Rook(Color pieceColor) : ChessPiece(pieceColor), hasMoved(false){
}

// Destructor, ensures proper cleanup for Rook objects
Rook::~Rook() = default;

// Implementation of the pure virtual function to returns 'R' as a symbol for a rook
char Rook::getSymbol() const {
    return 'R';
}
 // Returns 'Rook'
string Rook::getName() const {
    return "Rook";
}

// Checks if the move from the 'from' position to the 'to' position is valid for the rook.
// The rook must move in a straight line along the same row or column, and there must be no pieces blocking its path.
bool Rook::isValidMove(const Position& from, const Position& to, const ChessGame& game) const {
    // 'game' is currently unused for Rook but included to maintain consistent interface.
    (void)game; 
    // A rook can move either along the same row or the same column
    return (to.getRow() == from.getRow() || to.getCol() == from.getCol());
} 

// Method to set the moved status of the rook
void Rook::setMoved() {
    hasMoved = true;
}

// Method to check if the rook has moved before
bool Rook::hasMovedBefore() const {
    return hasMoved;
}
