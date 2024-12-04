// Knight.cpp
#include "Knight.h"
#include "ChessGame.h"

// Constructor that sets the color of the knight
Knight::Knight(Color pieceColor) : ChessPiece(pieceColor){
}

// Destructor, No specific resources to release for knight
Knight::~Knight() = default;

// Implementation of the pure virtual function to returns 'N' as a symbol for a knight
char Knight::getSymbol() const{
  return 'N';  
}
// Returns the name of the piece: "Knight"
string Knight::getName() const {
    return "Knight";
}

// Checks if the move from 'from' to 'to' is valid for the knight.
// Knights move in an L-shape: two squares in one direction and then one square perpendicular.
bool Knight::isValidMove(const Position& from, const Position& to, const ChessGame& game) const {
    // 'game' is currently unused for Knight but included to maintain consistent interface.
    (void)game; 
    int rowDifference = abs(to.getRow() - from.getRow());
    int colDifference = abs(to.getCol() - from.getCol());

    // A valid knight move is either two squares in one direction and one in the other
    return (rowDifference == 2 && colDifference == 1) || (rowDifference == 1 && colDifference == 2);
} 