// King.cpp
#include "King.h"
#include "ChessGame.h"

// Constructor that sets the color of the king
King::King(Color pieceColor) : ChessPiece(pieceColor), hasMoved(false) {
}

// Destructor, ensures proper cleanup for King objects
King::~King() {
}

// Implementation of the pure virtual function to get the symbol representing the piece
// Returns 'K' for a king
char King::getSymbol() const {
    return 'K';
}
 // Returns 'King'
string King::getName() const {
    return "King";
}

// Implementation of the pure virtual function to check if a move is valid for the king
// Kings move one square in any direction
bool King::isValidMove(const Position& from, const Position& to, const ChessGame& game) const {
    // 'game' is currently unused for King but included to maintain consistent interface.
    (void)game; 
    int rowDifference = abs(to.getRow() - from.getRow());
    int colDifference = abs(to.getCol() - from.getCol());

    // A valid king move is one square in any direction
    return (rowDifference <= 1 && colDifference <= 1) && (rowDifference + colDifference > 0);
}

// Method to set the moved status of the king
void King::setMoved() {
    hasMoved = true;
}

// Method to check if the king has moved before
bool King::hasMovedBefore() const {
    return hasMoved;
}