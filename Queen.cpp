// Queen.cpp
#include "Queen.h"
#include "ChessGame.h"

// Constructor that sets the color of the queen
Queen::Queen(Color pieceColor) : ChessPiece(pieceColor) {
}

// Destructor, ensures proper cleanup for Queen objects
Queen::~Queen() = default;

// Implementation of the pure virtual function to get the symbol representing the piece
// Returns the character symbol 'Q' representing the queen on the chessboard.
char Queen::getSymbol() const {
    return 'Q';
}
// Returns the string "Queen" representing the name of this piece.
string Queen::getName() const {
    return "Queen";
}

// Checks if the move from the 'from' position to the 'to' position is valid for the queen.
// A valid queen move must be along the same row, column, or diagonal.
bool Queen::isValidMove(const Position& from, const Position& to, const ChessGame& game) const {
    // 'game' is currently unused for Queen but included to maintain consistent interface.
    (void)game; 
    int rowDifference = abs(to.getRow() - from.getRow());
    int colDifference = abs(to.getCol() - from.getCol());

    // A valid queen move is either along the same row, the same column, or diagonally
    return (rowDifference == colDifference || to.getRow() == from.getRow() || to.getCol() == from.getCol());
}