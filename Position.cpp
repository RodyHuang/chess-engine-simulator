// Position.cpp
#include "Position.h"
#include <iostream>
#include <cctype> // for toupper

// Default constructor, initializes the position to an invalid state (-1, -1)
Position::Position() : row(-1), col(-1){
}

// Constructor that initializes the position from a coordinate string (e.g., "E2")
Position::Position(const string& posStr) : row(-1), col(-1){
    // The input must be exactly two characters long
    if (posStr.length() !=2){
        return; //invalid input, leave row and col as -1
    }
    
    char file = toupper(posStr[0]);
    char rank = posStr[1];

    // Check if the file is between 'A' and 'H', and rank is between '1' and '8'
    if((file >= 'A' && file <= 'H') && (rank >= '1' && rank <= '8')){
        // // Convert rank ('1' - '8') to row index (0 - 7), where '8' corresponds to 0 (topmost rank)
        row = 8 - (rank - '0');
        // Convert file ('A' - 'H') to column index (0 - 7), where 'A' corresponds to 0 (leftmost file)
        col = file - 'A';
    }
    // If the input is invalid, row and col remain -1, indicating an invalid position
}

// Constructor that initializes the position with row and column
Position::Position(int r, int c) {
    if (r >= 0 && r < 8 && c >= 0 && c < 8) {
        row = r;
        col = c;
    } else {
        row = -1;
        col = -1;
    }
}

// Checks if the position is within the bounds of a standard 8x8 chessboard.
bool Position::isValid() const{
    return((row >= 0 && row < 8) && (col >= 0 && col < 8));
}

// Overloads the equality operator to compare two positions
bool Position::operator==(const Position& other) const{
    return(row == other.row) && (col == other.col);
}

// Overloads the inequality operator to compare two positions
bool Position::operator!=(const Position& other) const{
    return !(*this == other);
}

// Getter for the row index
int Position::getRow() const{
    return row;
}

// Getter for the cpl index
int Position::getCol() const{
    return col;
}

// Overloads the << operator to provide a human-readable representation of the chess position.
// If the position is valid, it will be displayed in standard chess notation (e.g., "E2").
// If invalid, it will indicate so.
ostream& operator<<(ostream& os, const Position& pos) {
    if (pos.isValid()) {
        char file = 'A' + pos.col; // Convert column to character (e.g., 0 -> 'A', 1 -> 'B', etc.)
        char rank = '8' - pos.row; // Convert row to rank (e.g., 0 -> '8', 7 -> '1', etc.)
        os << file << rank;
    } else {
        os << "Invalid Position";
    }
    return os;
}