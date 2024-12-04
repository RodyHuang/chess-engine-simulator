// ChessPiece.h
// ChessPiece is an abstract base class, which serves as a blueprint for all chess pieces.
// It provides a common interface for setting the piece color, getting the piece symbol, and validating moves.

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "Position.h"
#include "ChessGame.h"
#include "Color.h"
#include <string>
using namespace std;

// Base class representing a chess piece
class ChessPiece{
protected:
    Color color; // Color of the chess piece (WHITE or BLACK)

public:
    // Constructor that sets the color of the chess piece
    ChessPiece(Color pieceColor);

    // Virtual destructor
    virtual ~ChessPiece();

    // Getter for the color of the piece
    Color getColor() const;

    // Returns the character symbol representing the chess piece.
    // For example, a pawn might return 'P', a rook might return 'R'.
    virtual char getSymbol() const = 0;

    // Returns the name of the chess piece (e.g., "Pawn", "Rook").
    virtual string getName() const = 0;

    // Pure virtual function to check if a move is valid for the piece
    virtual bool isValidMove(const Position& from, const Position& to, const ChessGame& game) const = 0;
};

#endif // CHESSPIECE_H