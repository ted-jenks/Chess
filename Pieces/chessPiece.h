/*
File: chessPiece.h
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: h file for the chess piece for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "../Position/position.h"
#include <iostream>
#include <string>

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

enum Colour
{
    white = 1,
    black = -1
};

enum Type
{
    pawn,
    rook,
    knight,
    bishop,
    queen,
    king
};

class ChessPiece
{
protected:
    int numMoves = 0;
    Colour colour;
    std::string symbol;
    Type type;
    ChessPiece(Type type) noexcept;
    ChessPiece(ChessPiece const &other) noexcept;
    ChessPiece(Colour colour, Type type) noexcept;
    ChessPiece &operator=(ChessPiece const &other) noexcept;
    // function to check if the start and end position are the same
    // precondition: function passed a start and end position
    // postcondition: return true if allowed
    bool differentSquare(Position positionStart, //
                         Position positionEnd) const noexcept;
    // function to check if move is diagonal
    // precondition: function passed a start and end position
    // postcondition: return true if diagonal
    bool diagonalMove(Position positionStart, //
                      Position positionEnd) const noexcept;
    // function to check if move is straight
    // precondition: function passed a start and end position
    // postcondition: return true if straight
    bool straightMove(Position positionStart, //
                      Position positionEnd) const noexcept;

public:
    virtual ~ChessPiece() noexcept = default;
    // virtual function to check if a move is allowed
    // precondition: function passed a start and end position
    // postcondition: return true if allowed
    virtual bool moveAllowed(Position positionStart, //
                             Position positionEnd) const noexcept = 0;
    // virtual function to check if a taking move is allowed
    // precondition: function passed a start and end position
    // postcondition: return true if allowed
    virtual bool takingMoveAllowed(Position positionStart, //
                                   Position positionEnd) const noexcept = 0;
    // function to get the colour of a piece
    // precondition:
    // postcondition: return colour
    Colour getColour() const noexcept;
    // function to return the symbol of a piece
    // precondition:
    // postcondition: return symbol
    std::string getSymbol() const noexcept;
    // function to return the type of a piece
    // precondition:
    // postcondition: return type
    Type getType() const noexcept;
    // function to return the number of moves that a piece has made
    // precondition:
    // postcondition: return number of moves
    int getNumMoves() const noexcept;
    // function to return the type of a piece as a string
    // precondition:
    // postcondition: return type string
    std::string getName() const noexcept;
    // function to note that the piece has been moved
    // precondition:
    // postcondition: iterate number of moves
    void moved() noexcept;
};

#endif