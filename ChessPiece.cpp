// ChessPiece.cpp
#include "ChessPiece.h"
#include "ChessGame.h"

// Constructor that sets the color of the chess piece
ChessPiece::ChessPiece(Color pieceColor) : color(pieceColor){
}

// Virtual destructor implementation
ChessPiece::~ChessPiece() {
    // Virtual destructor to allow derived classes to release resources, if necessary.
}

// Getter for the color of the piece
Color ChessPiece::getColor() const{
        return color;
}