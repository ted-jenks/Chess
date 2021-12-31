/*
File: queen.cpp
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: cpp file for the queen for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "../Position/position.h"
#include "chessPiece.h"
#include "queen.h"
#include <string>

Queen::Queen() noexcept : ChessPiece(queen)
{
    symbol = "♕";
}
Queen::Queen(Colour colour) noexcept : ChessPiece(colour, queen)
{
    symbol = (colour == white) ? "♕" : "♛";
}
bool Queen::moveAllowed(Position positionStart, //
                        Position positionEnd) const noexcept
{
    if (!ChessPiece::differentSquare(positionStart, positionEnd))
        return false;
    if (ChessPiece::diagonalMove(positionStart, positionEnd))
        return true;
    if (ChessPiece::straightMove(positionStart, positionEnd))
        return true;
    return false;
}
bool Queen::takingMoveAllowed(Position positionStart, //
                              Position positionEnd) const noexcept
{
    return moveAllowed(positionStart, positionEnd); // no different taking move
}