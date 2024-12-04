// Pawn.h
// Pawn class inherits from the ChessPiece base class and provides specific behavior for pawns.

#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"
#include "ChessGame.h"
#include "Color.h"

// Pawn class representing a pawn chess piece
class Pawn : public ChessPiece{
public:
    // Constructor that sets the color of the pawn
    Pawn(Color pieceColor);

    // Destructor, ensures proper cleanup for Pawn objects
    ~Pawn() override;
    
    // Implementation of the pure virtual function to get the symbol representing the piece
    // Returns 'P' to represent a pawn
    char getSymbol() const override;
    // Returns 'Pawan'
    string getName() const override;

    // Implementation of the pure virtual function to check if a move is valid for the pawn
    bool isValidMove(const Position& from, const Position& to, const ChessGame& game) const override;
};

#endif // PAWN_H