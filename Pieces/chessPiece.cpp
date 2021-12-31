/*
File: chessPiece.cpp
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: cpp file for the chess piece for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "chessPiece.h"
#include "../Position/position.h"
#include <string>
#include <cmath>

ChessPiece::ChessPiece(Type type) noexcept : type(type) {}
ChessPiece::ChessPiece(ChessPiece const &other) noexcept { *this = other; }
ChessPiece::ChessPiece(Colour colour, Type type) noexcept //
    : colour(colour), type(type)
{
}
bool ChessPiece::differentSquare(Position positionStart, //
                                 Position positionEnd) const noexcept
{
    if (positionStart.getColumn() == positionEnd.getColumn() //
        && positionStart.getRow() == positionEnd.getRow())
        return false;
    return true;
}
bool ChessPiece::diagonalMove(Position positionStart, //
                              Position positionEnd) const noexcept
{
    int columnDif, rowDif;
    columnDif = std::abs(positionStart.getColumn() - positionEnd.getColumn());
    rowDif = std::abs(positionStart.getRow() - positionEnd.getRow());
    if (rowDif == columnDif)
        return true;
    return false;
}
bool ChessPiece::straightMove(Position positionStart, //
                              Position positionEnd) const noexcept
{
    if (positionStart.getColumn() == positionEnd.getColumn() //
        || positionStart.getRow() == positionEnd.getRow())
        return true;
    return false;
}
Colour ChessPiece::getColour() const noexcept { return colour; }
std::string ChessPiece::getSymbol() const noexcept { return symbol; }
Type ChessPiece::getType() const noexcept { return type; }
int ChessPiece::getNumMoves() const noexcept { return numMoves; }
void ChessPiece::moved() noexcept { numMoves++; }
std::string ChessPiece::getName() const noexcept
{
    switch (type)
    {
    case queen:
        return "Queen";
    case bishop:
        return "Bishop";
    case rook:
        return "Rook";
    case knight:
        return "Knight";
    case king:
        return "King";
    case pawn:
        return "Pawn";
    }
    return "No Type";
}
ChessPiece &ChessPiece::operator=(ChessPiece const &other) noexcept
{
    if (this == &other) // guard self-assignment
        return *this;

    colour = other.colour;
    symbol = other.symbol;
    return *this;
}