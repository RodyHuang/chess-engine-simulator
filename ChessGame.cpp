// ChessGame.cpp
#include "ChessGame.h"
#include "Position.h" 
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <sstream>
using namespace std;

// Constructor that initializes an empty chessboard
ChessGame::ChessGame() {
    // Initialize all positions to nullptr directly
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            board[row][col] = nullptr;
        }
    }

    currentTurn = WHITE; // Set the initial turn to WHITE
    whiteKingSideCastling = whiteQueenSideCastling = true; // Allow castling for white initially
    blackKingSideCastling = blackQueenSideCastling = true; // Allow castling for black initially
}

// Destructor that ensures proper cleanup of all chess pieces
ChessGame::~ChessGame() {
    // Delete all pieces from the board by the helper function
    clearBoard();
}

// Method to initialize the board with a given FEN string
void ChessGame::loadState(const string& fen) {
    // Clear the board first
    clearBoard();
    
    // Import the FEN string 
    istringstream fenStream(fen); // Create a string stream to parse the FEN string
    string piecePlacement, activeColor, castlingAvailability; // Define the string variables for piece placement, active color, and castling availability respectively
    fenStream >> piecePlacement >> activeColor >> castlingAvailability; // Extract from the FEN string
    if (piecePlacement.empty() || activeColor.empty() || castlingAvailability.empty()) { //Chekc if the format of the FEN string is valid
        cout << "Invalid FEN string format." << endl;
        return;
    }

    // Initialize the board with the given FEN
    int row = 0;
    int col = 0;
    for (char c : piecePlacement) { // Iterate through each character in the FEN piece placement string 
        if (c == '/') {
            row++; // Move to the next row
            col = 0; // Reset column to the start
        } else if (isdigit(c)) {
            col += c - '0'; // Skip the number of empty squares indicated by the digit
        } else {
            Color color = isupper(c) ? WHITE : BLACK; // Determine the color of the piece based on whether the character is uppercase or lowercase
            c = tolower(c); // Convert to lowercase for the switch() function later
            ChessPiece* piece = nullptr; //Create a pointer to ChessPiece and point to null

            switch (c) { // Create the appropriate piece based on the character
                case 'p': piece = new Pawn(color); break;
                case 'r': piece = new Rook(color); break;
                case 'n': piece = new Knight(color); break;
                case 'b': piece = new Bishop(color); break;
                case 'q': piece = new Queen(color); break;
                case 'k': piece = new King(color); break;
            }

            board[row][col] = piece; // Place the piece on the board
            col++; // Move to the next column
        }
    }

    // Set the current turn based on the FEN string with error check
    if (activeColor == "w") {
        currentTurn = WHITE;
    } else if (activeColor == "b") {
        currentTurn = BLACK;
    } else {
        cout << "Invalid active color in FEN string." << endl;
        return;
    }

    // Set castling availability based on the FEN string
    whiteKingSideCastling = (castlingAvailability.find('K') != std::string::npos); // Check if white can castle kingside
    whiteQueenSideCastling = (castlingAvailability.find('Q') != std::string::npos); // Check if white can castle queenside
    blackKingSideCastling = (castlingAvailability.find('k') != std::string::npos); // Check if black can castle kingside
    blackQueenSideCastling = (castlingAvailability.find('q') != std::string::npos); // Check if black can castle queenside

    cout << "A new board state is loaded!" << endl;
}


// Method to submit a move
bool ChessGame::submitMove(const string& fromStr, const string& toStr) {
    Position from = Position(fromStr); //Convert the input string to a Position
    Position to = Position(toStr); //Convert the input string to a Position
    return Move(from, to);
}

// Method to check the validity of a move
bool ChessGame::Move(const Position& from, const Position& to) {
    // Get the piece at the source position
    ChessPiece* piece = getPieceAt(from);
    
    // General check for the move (e.g., turn color, valid position, from-to cannot be the same)
    if (!initialCheck(from, to)){
        return false;
    }

    // Check if this is a castling move
    if (piece->getSymbol() == 'K' && abs(to.getCol() - from.getCol()) == 2) {
        // Call performCastling to handle castling logic
        if (performCastling(from, to)) {
            // Update the turn
            currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
            return true;
        }
        cout << "Not valid castling" << endl;
        return false;
    }

    // If not a castling move, then proceed with regular move logic
    // Check if the move of the piece is valid by the moving rule of each piece 
    if (!piece->isValidMove(from, to, *this)) { 
        printInvalidMoveMessage(piece, to); // Call helpter function to output message of invlid move
        return false;
    }

    // Additional check for the pieces that require the path between 'from' and 'to' is clear (Bishop, Rook, Queen))
    char pieceSymbol = piece->getSymbol();
    if (pieceSymbol == 'R' || pieceSymbol == 'B' || pieceSymbol == 'Q') {
        if (!isPathClear(from, to)) {
            printInvalidMoveMessage(piece, to);
            return false;
        }
    }

    // Check if the destination position is occupied by the current player's piece
    ChessPiece* targetPiece = board[to.getRow()][to.getCol()];
    if (targetPiece != nullptr && targetPiece->getColor() == piece->getColor()) {
        printInvalidMoveMessage(piece, to);
        return false;
    }

    // Make the piece move
    ChessPiece* capturedPiece = board[to.getRow()][to.getCol()];
    board[to.getRow()][to.getCol()] = piece;
    board[from.getRow()][from.getCol()] = nullptr;

    // Check if the move puts the current player's king in check 
    if (isKingInCheck(piece->getColor())) {
        // If yes, Undo the move
        board[from.getRow()][from.getCol()] = piece;
        board[to.getRow()][to.getCol()] = capturedPiece;
        cout << "Move puts your own king in check." << endl;
        return false; // Return false if the move is illegal
    }

    // If the move does not lead to a check, then finalize the move
    // Generate the move message before actually moving the piece
    string color = (piece->getColor() == WHITE ? "White's " : "Black's ");
    if (capturedPiece != nullptr) {
        cout << color << piece->getName() << " moves from " << from << " to " << to << " taking " << (piece->getColor() == WHITE ? "Black's " : "White's ") << capturedPiece->getName() << endl;;
    }else{
        cout << color << piece->getName() << " moves from " << from << " to " << to << endl;
    }

    // Delete captured piece
    if (capturedPiece != nullptr) {
        delete capturedPiece;
    }

    // Check if the opponent's king is in check or checkmate after the move
    Color opponentColor = (currentTurn == WHITE) ? BLACK : WHITE;
    if (isKingInCheck(opponentColor)) {       
        if (isCheckmate(opponentColor)) {
            cout << (opponentColor == WHITE ? "White" : "Black") << " is in checkmate" << endl;
            return true; // Game over
        }
        cout << (opponentColor == WHITE ? "White" : "Black") << " is in check" << endl;
    } else if (isStalemate(opponentColor)) {
        cout << (opponentColor == WHITE ? "White" : "Black") << " is in stalemate" << endl;
        return true; // Game over
    }

    // Update the current turn
    currentTurn = (currentTurn == WHITE) ? BLACK : WHITE; // Switch the turn to the other player
    return true; // Return true to indicate the move was successful
}


// General check for the move (e.g., turn color, valid position, from-to cannot be the same)
bool ChessGame::initialCheck(const Position& from, const Position& to) const{
    // Get the piece at the source position
    ChessPiece* piece = getPieceAt(from);
  
    // Check if there is no piece at the source position
    if (piece == nullptr) {
        cout << "There is no piece at position " << from << "!" << endl;
        return false; 
    }

    // Check if the moving piece belongs to the cuurent player
    if (piece->getColor() != currentTurn) {
        cout << "It is not " << (currentTurn == WHITE ? "Black's" : "White's") << " turn to move!" << endl;
        return false;
    }

    // Check if both positions are valid
    if (!from.isValid() || !to.isValid()) {
        printInvalidMoveMessage(piece, to);
        return false;
    }

    // Check if both positions are the same
    if (from == to) {
        printInvalidMoveMessage(piece, to);
        return false;
    }  
    return true;
}

// Method to check if the path between 'from' and 'to' is clear (i.e., no pieces in the way)
bool ChessGame::isPathClear(const Position& from, const Position& to) const {
    // Determine the direction of movement for rows and columns
    int rowDiff = to.getRow() - from.getRow();
    int colDiff = to.getCol() - from.getCol();
    
    // Calculate the direction of movement: +1, -1, or 0
    int rowDirection = (rowDiff != 0) ? rowDiff / abs(rowDiff) : 0;
    int colDirection = (colDiff != 0) ? colDiff / abs(colDiff) : 0;

    // Start from the next position in the direction of movement
    int currentRow = from.getRow() + rowDirection;
    int currentCol = from.getCol() + colDirection;

    // Traverse the path from 'from' to 'to' but stop before reaching 'to'
    while (currentRow != to.getRow() || currentCol != to.getCol()) {
        // If there is a piece at the current position, the path is blocked
        if (board[currentRow][currentCol] != nullptr) {
            return false; // The path is blocked by another piece
        }
        // Move to the next position in the direction of movement
        currentRow += rowDirection;
        currentCol += colDirection;
    }
    // If we reach here, it means there were no pieces blocking the path
    return true; // The path is clear
}

// Method to check if a king is in check
bool ChessGame::isKingInCheck(Color kingColor) const {
    Position kingPosition;
    bool kingFound = false; // Flag to check if king is found

    // Find the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            ChessPiece* piece = board[row][col];
            if (piece != nullptr && piece->getSymbol() == 'K' && piece->getColor() == kingColor) {
                kingPosition = Position(row, col);
                kingFound = true; // Set flag to true once the king is found
                break;
            }
        }
        if (kingFound) break; // If king is found, exit the outer loop as well
    }

    // Check if any opposing piece can attack the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            ChessPiece* piece = board[row][col];
            if (piece != nullptr && piece->getColor() != kingColor) { // Check if the piece is an opponent's
                Position from(row, col);

                // Check if the move is valid for the attacking piece and if the path is clear (if applicable)
                if (piece->isValidMove(from, kingPosition, *this) && isPathClear(from, kingPosition)) {
                    return true; // King is in check
                }
            }
        }
    }
    return false; // King is not in check
}

// Method to check if the king is in checkmate
bool ChessGame::isCheckmate(Color kingColor) {
    // Iterate through all pieces of the given color to find any valid move
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            ChessPiece* piece = board[row][col];
            if (piece != nullptr && piece->getColor() == kingColor) {
                Position from(row, col);
                
                // Try all possible moves for the piece
                for (int r = 0; r < 8; ++r) {
                    for (int c = 0; c < 8; ++c) {
                        Position to(r, c);

                        // Check if the move is valid for the piece
                        if (piece->isValidMove(from, to, *this) && from!=to) {
                            // Additional path check for specific pieces to have clear path (Bishop, Rook, Queen)
                            if ((piece->getSymbol() == 'R' || piece->getSymbol() == 'B' || piece->getSymbol() == 'Q') && !isPathClear(from, to)) {
                                continue;
                            }
                            // Check if the destination position is occupied by the current player's piece
                            ChessPiece* capturedPiece = board[r][c];
                            if (capturedPiece != nullptr && capturedPiece->getColor() == piece->getColor()) {
                                continue;
                            }
                            
                            // Temporarily make the move
                            board[r][c] = piece;
                            board[row][col] = nullptr;

                            // Check if the move puts the current player's king in check 
                            bool kingInCheck = isKingInCheck(kingColor);
                            
                            // Undo the move
                            board[row][col] = piece;
                            board[r][c] = capturedPiece;

                            // If any move can prevent the king from being in check, it is not checkmate
                            if (!kingInCheck) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true; // If no valid moves prevent check, then it's checkmate
}

// Method to check if there is a stalemate
bool ChessGame::isStalemate(Color color) {
    if (isKingInCheck(color)) {
        return false; // If it's in a check, then it must not a Stalemate
    }

    // Iterate through all pieces of the given color
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            ChessPiece* piece = board[row][col];
            if (piece != nullptr && piece->getColor() == color) {
                Position from(row, col);
                // Try all possible moves for the piece
                for (int r = 0; r < 8; ++r) {
                    for (int c = 0; c < 8; ++c) {
                        Position to(r, c);
                        if (piece->isValidMove(from, to, *this)) {
                            // Temporarily make the move and check if it lead to a check
                            ChessPiece* capturedPiece = board[r][c];
                            board[r][c] = piece;
                            board[row][col] = nullptr;

                            bool kingInCheck = isKingInCheck(color);

                            // Undo the move
                            board[row][col] = piece;
                            board[r][c] = capturedPiece;

                            if (!kingInCheck) {
                                return false; // If there is a move that does not lead to a check, then it is not a stalmate
                            }
                        }
                    }
                }
            }
        }
    }
    return true; // If there is no any valid move, then it is a stalmate
}


// Function to validate and execute castling
bool ChessGame::performCastling(const Position& from, const Position& to) {
    // Get the piece to be moved
    ChessPiece* piece = getPieceAt(from);

    // Ensure the piece is a king
    if (piece->getSymbol() != 'K') {
        return false;
    }

    // Determine if this is king-side or queen-side castling
    bool isKingSide = (to.getCol() > from.getCol());

    // Define rook's current and target positions
    Position rookPos = isKingSide ? Position(from.getRow(), 7) : Position(from.getRow(), 0);
    Position rookTargetPos = isKingSide ? Position(from.getRow(), 5) : Position(from.getRow(), 3);

    ChessPiece* rook = getPieceAt(rookPos);

    // Verify castling conditions: king and rook must not have moved
    King* kingPtr = dynamic_cast<King*>(piece);
    if (kingPtr == nullptr || kingPtr->hasMovedBefore()) {
        cout << "Invalid castling move: king condition not met." << endl;
        return false;
    }

    Rook* rookPtr = dynamic_cast<Rook*>(rook);
    if (rookPtr == nullptr || rookPtr->hasMovedBefore()) {
        cout << "Invalid castling move: rook condition not met." << endl;
        return false;
    }

    // Check if the king is currently in check
    if (isKingInCheck(piece->getColor())) {
        cout << "Cannot castle while in check." << endl;
        return false;
    }

    // Verify that the path is clear and safe for the king
    int direction = isKingSide ? 1 : -1;
    for (int col = from.getCol() + direction; col != to.getCol() + direction; col += direction) {
        Position intermediatePos(from.getRow(), col);
        if (isOccupied(intermediatePos) || 
            (col != rookPos.getCol() && isKingInCheckAfterMove(from, intermediatePos))) {
            cout << "Invalid castling move: path not clear or king passes through threatened square." << endl;
            return false;
        }
    }

    // Execute the castling move
    board[to.getRow()][to.getCol()] = piece;
    board[from.getRow()][from.getCol()] = nullptr;
    board[rookTargetPos.getRow()][rookTargetPos.getCol()] = rook;
    board[rookPos.getRow()][rookPos.getCol()] = nullptr;

    // Mark both the king and rook as having moved
    kingPtr->setMoved();
    rookPtr->setMoved();

    cout << "Castling move performed" << endl;
    return true;
}


//Method to check if a king will be in check when performing castling
bool ChessGame::isKingInCheckAfterMove(const Position& from, const Position& to) {
    // Store the original piece at the destination
    ChessPiece* originalPiece = board[to.getRow()][to.getCol()];
    ChessPiece* movingPiece = board[from.getRow()][from.getCol()];

    // Temporarily make the move
    board[to.getRow()][to.getCol()] = movingPiece;
    board[from.getRow()][from.getCol()] = nullptr;

    // Determine the color of the king being checked
    Color kingColor = movingPiece->getColor();

    // Check if the move leads to the king being in check
    bool inCheck = isKingInCheck(kingColor);

    // Undo the move
    board[from.getRow()][from.getCol()] = movingPiece;
    board[to.getRow()][to.getCol()] = originalPiece;

    return inCheck;
}

// Method to print the current state of the chessboard(not required by Spec, but useful for checking)
void ChessGame::printBoard() const{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) { 
            if (board[row][col] == nullptr) { // If there is no piece at the current position
                cout << ". "; // Print a dot to indicate an empty square
            } else {
                char symbol = board[row][col]->getSymbol();
                if (board[row][col]->getColor() == WHITE) {
                    cout << static_cast<char>(toupper(symbol)) << " "; // Print white pieces in uppercase
                } else {
                    cout << static_cast<char>(tolower(symbol)) << " "; // Print black pieces in lowercase
                }
            }   
        }
        cout << endl; // Move to the next line after each row
    }
}


// Helper function to clear the board
void ChessGame::clearBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete board[row][col];
            board[row][col] = nullptr;
        }
    }
}

// Helper function to print invalid move messages
void ChessGame::printInvalidMoveMessage(const ChessPiece* piece, const Position& to) const {
    cout << (piece->getColor() == WHITE ? "White's " : "Black's ") << piece->getName() << " cannot move to " << to << "!" << endl;
}

// Helper function to check if a position is occupied
bool ChessGame::isOccupied(const Position& pos) const {
    return board[pos.getRow()][pos.getCol()] != nullptr;
}

// Helper function to get the piece at a given position
ChessPiece* ChessGame::getPieceAt(const Position& pos) const {
    return board[pos.getRow()][pos.getCol()];
}