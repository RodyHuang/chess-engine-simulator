// Position.h
// Position class represents a position on a chessboard. 
// It provides methods to initialize, validate, and compare positions in a chass game.

#ifndef POSITION_H
#define POSITION_H

#include<string>
using namespace std;

// Position class used to represent a position on a chessboard
class Position {
private:
    int row; // Row index, ranging from 0 (8th rank) to 7 (1st rank), where 0 represents the topmost 8th rank
    int col; // Column index, ranging from 0 (file 'A') to 7 (file 'H'), where 0 represents the leftmost file 'A'

public:
    // Default constructor, initializes the position to an invalid state (-1, -1)
    Position();

    // Constructor that initializes the position from a coordinate string (e.g., "C3")
    Position(const string& posStr);
    
    // Constructor that initializes the position with row and column
    Position(int r, int c);

    // Checks if the position is within the bounds of a standard 8x8 chessboard.
    bool isValid() const;

    // Overloads the equality operator to compare two positions
    bool operator==(const Position& other) const;

    // Overloads the inequality operator to compare two positions
    bool operator!=(const Position& other) const;

    // Getter for the row index
    int getRow() const;

    // Getter for the column index
    int getCol() const;

    // Overloads the << operator for printing a Position in a human-readable format (e.g., "C3").
    friend ostream& operator<<(ostream& os, const Position& pos);
};

#endif 