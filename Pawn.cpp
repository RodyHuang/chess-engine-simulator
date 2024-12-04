// Pawn.cpp
#include "Pawn.h"
#include "ChessGame.h"

// Constructor that sets the color of the pawn
Pawn::Pawn(Color pieceColor) : ChessPiece(pieceColor){
}

// Destructor, No specific resources to release for Pawn
Pawn::~Pawn() {
}

// Returns the character symbol 'P' representing the pawn on the chessboard.
char Pawn::getSymbol() const{
  return 'P';  
}
 // Returns the string "Pawn", which represents the name of this piece.
string Pawn::getName() const {
    return "Pawn";
}

// Checks if the move from the 'from' position to the 'to' position is valid for the pawn.
// A pawn can move forward one square, or two squares from its initial position.
// A pawn captures diagonally, and can also perform en passant under specific conditions.
bool Pawn::isValidMove(const Position& from, const Position& to, const ChessGame& game) const{
    // Check if the move is within the same column (for forward moves)
    if(from.getCol() == to.getCol()){
        int rowDiff = to.getRow() - from.getRow();
        // Handling white pawn movement
        if (color == WHITE) {
            // Check if the white pawn is making an initial two-square move, and if the path is clean
            if (from.getRow() == 6 && rowDiff == -2 && !game.isOccupied(to) && !game.isOccupied(Position(5, from.getCol()))) {
                return true;
            }
            // Check if the white pawn is making a regular one-square move
            else if (rowDiff == -1 && !game.isOccupied(to)) {
                return true;
            }

        // Handling black pawn movement
        } else if (color == BLACK) {
            // Check if the black pawn is making an initial two-square move, and if the path is clean
            if (from.getRow() == 1 && rowDiff == 2 && !game.isOccupied(to) && !game.isOccupied(Position(2, from.getCol()))) {
                return true; // Valid initial two-square move for black pawn
            }
            // Check if the black pawn is making a regular one-square move
            else if (rowDiff == 1 && !game.isOccupied(to)) {
                return true; // Valid one-square forward move for black pawn
            }
        }   
    } 
    // Check if the move is a valid capture(diagonal move)
    if(abs(from.getCol()-to.getCol()) == 1){ // Check if move exactly one column apart
        int rowDiff = to.getRow() - from.getRow();
        // Check for white pawns(move diagonally upwards)
        if(color == WHITE && rowDiff == -1){
            return true;
        // Check for black pawns(move diagonally downwards)
        }else if(color == BLACK && rowDiff == 1){
            return true;
        }
    }
    // If none of the above conditions are met, the move is not valid for a pawn
    return false;
}