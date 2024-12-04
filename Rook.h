// Rook.h
// The Rook class inherits from the ChessPiece base class and provides specific behavior for rooks.

#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"
#include "ChessGame.h"
#include "Color.h"

class Rook : public ChessPiece {
private:
    bool hasMoved; // Flag to indicate if the rook has moved before --> for "Castling"
public:
    // Constructor that sets the color of the rook
    Rook(Color pieceColor);

    // Destructor, ensures proper cleanup for Rook objects
    ~Rook() override;

    // Implementation of the pure virtual function to get the symbol representing the piece
    // Returns 'R' to represent a rook
    char getSymbol() const override;
    // Returns 'Rook'
    string getName() const override;

    // Implementation of the pure virtual function to check if a move is valid for the knight
    bool isValidMove(const Position& from, const Position& to, const ChessGame& game) const override;

    // Marks the rook as having moved, which is used to invalidate castling opportunities.
    void setMoved();

    // Flag to indicate if the rook has moved before, used for validating castling conditions.
    bool hasMovedBefore() const;
};

#endif // ROOK_H
