// King.h
// The King class inherits from the ChessPiece base class and provides specific behavior for kings.

#ifndef KING_H
#define KING_H

#include "ChessPiece.h"
#include "ChessGame.h"
#include "Color.h"

// King class representing a king chess piece
class King : public ChessPiece {
private:
    bool hasMoved;  // Attribute to track if the king has moved --> for "Castling"

public:
    // Constructor that sets the color of the king
    King(Color pieceColor);

    // Destructor, ensures proper cleanup for King objects
    ~King() override;

    // Implementation of the pure virtual function to get the symbol representing the piece
    // Returns 'K' to represent a king
    char getSymbol() const override;
    // Returns the string "King", representing the name of this piece
    string getName() const override;

    // Checks if the move from 'from' position to 'to' position is valid for the king.
    // A king moves one square in any direction. Additionally, castling is allowed under specific conditions.
    bool isValidMove(const Position& from, const Position& to, const ChessGame& game) const override;

    // Marks the king as having moved, which affects the availability of castling in the game
    void setMoved();

    // Checks if the king has moved before; used to determine if castling is allowed
    bool hasMovedBefore() const;
};

#endif // KING_H