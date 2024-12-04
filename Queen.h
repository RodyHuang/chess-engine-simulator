// Queen.h
// The Queen class inherits from the ChessPiece base class and provides specific behavior for queens.

#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "ChessGame.h"
#include "Color.h"

// Queen class representing a queen chess piece
class Queen : public ChessPiece {
public:
    // Constructor that sets the color of the queen
    Queen(Color pieceColor);

    // Destructor, ensures proper cleanup for Queen objects
    ~Queen() override;

    // Implementation of the pure virtual function to get the symbol representing the piece
    // Returns 'Q' to represent a queen
    char getSymbol() const override;
    // Returns 'Queen'
    string getName() const override;
    
    // Checks if the move from the 'from' position to the 'to' position is valid for the queen.
    // A queen moves in a straight line either along a row, a column, or a diagonal.
    bool isValidMove(const Position& from, const Position& to, const ChessGame& game) const override;
};

#endif // QUEEN_H