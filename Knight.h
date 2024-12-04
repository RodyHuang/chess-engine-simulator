// Knight.h
// The Knight class inherits from the ChessPiece base class and provides specific behavior for knights.

#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"
#include "ChessGame.h"
#include "Color.h"

class Knight : public ChessPiece {
public:
    // Constructor that sets the color of the knight
    Knight(Color pieceColor);

    // Destructor, ensures proper cleanup for Knight objects
    ~Knight() override;

    // Implementation of the pure virtual function to get the symbol representing the piece
    // Returns 'N' to represent a knight
    char getSymbol() const override;
    // Returns the name of the piece: "Knight"
    string getName() const override;
    
    // Checks if the move from 'from' position to 'to' position is valid for the knight.
    // Knights move in an L-shape: two squares in one direction and one square in the perpendicular direction.
    bool isValidMove(const Position& from, const Position& to, const ChessGame& game) const override;
};

#endif // KNIGHT_H
