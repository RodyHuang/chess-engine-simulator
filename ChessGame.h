// ChessGame.h
// This file defines the ChessGame class, which represents the chessboard and manages the state of a chess game.

#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Position.h"
#include "Color.h"

using namespace std;

class ChessPiece;

// ChessGame class representing a chessboard and managing the state of a chess game
class ChessGame {
private:
    // A 2D array to store pointers to chess pieces, representing the board. A nullptr represents an empty square.
    ChessPiece* board[8][8];

    // Represents the current player's turn, either WHITE or BLACK
    Color currentTurn;

    // Flags to track castling availability for each side (kingside or queenside)
    bool whiteKingSideCastling;
    bool whiteQueenSideCastling;
    bool blackKingSideCastling;
    bool blackQueenSideCastling;

public:
    // Constructor that initializes an empty chessboard
    ChessGame();
     // Destructor that ensures proper cleanup of all chess pieces
    ~ChessGame();

    // Loads the board state from a given FEN string, initializing the chessboard accordingly.
    void loadState(const string& fen);

    // Submits a move from 'fromStr' to 'toStr', which are string representations of the positions.
    bool submitMove(const string& fromStr, const string& toStr);

    // Executes the move from 'from' to 'to'. Returns true if the move is successful, false otherwise.
    bool Move(const Position& from, const Position& to);
    
    // Performs initial checks for the move, such as turn validation, position validity, and ensuring the move is not null.
    bool initialCheck(const Position& from, const Position& to) const;

    // Checks if the path between 'from' and 'to' is clear of any pieces.
    bool isPathClear(const Position& from, const Position& to) const;
    
    // Checks if the king of the given color is in check.
    bool isKingInCheck(Color kingColor) const;
    
    // Checks if the king of the given color is in checkmate.
    bool isCheckmate(Color kingColor);
    
    //Method to check if it is a stalmate
    bool isStalemate(Color color);
    
    //Method to check if a king will be in check when castling
    bool isKingInCheckAfterMove(const Position& from, const Position& to);
    
    // Method to print the current state of the chessboard
    void printBoard() const;

    // Helper function to clear the board
    void clearBoard();

    // Helper function to print invalid move messages
    void printInvalidMoveMessage(const ChessPiece* piece, const Position& to) const;

    // Method to check if a position is occupied
    bool isOccupied(const Position& pos) const;

    // Method to get the piece at a given position. Returns a pointer to the piece, or nullptr if no piece is present
    ChessPiece* getPieceAt(const Position& pos) const;

    // Performs a castling move from 'from' to 'to', if allowed by game rules
    bool performCastling(const Position& from, const Position& to);
};

#endif // CHESSGAME_H