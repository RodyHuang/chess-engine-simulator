// Bishop.h
// The Bishop class inherits from the ChessPiece base class and provides specific behavior for bishops.

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"
#include "ChessGame.h"
#include "Color.h"

// Bishop class representing a bishop chess piece
class Bishop : public ChessPiece {
public:
    // Constructor that sets the color of the bishop
    Bishop(Color pieceColor);

    // Destructor, ensures proper cleanup for Bishop objects
    ~Bishop() override;

    // Implementation of the pure virtual function to get the symbol representing the piece
    // Returns 'B' to represent a bishop
    char getSymbol() const override;
    // Returns 'Bishop'
    string getName() const override;

    // Implementation of the pure virtual function to check if a move is valid for the bishop
    bool isValidMove(const Position& from, const Position& to, const ChessGame& game) const override;
};

#endif // BISHOP_H

