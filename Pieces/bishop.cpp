/*
File: bishop.cpp
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: cpp file for the bishop for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "../Position/position.h"
#include "chessPiece.h"
#include "bishop.h"
#include <cmath>
#include <string>

Bishop::Bishop() noexcept : ChessPiece(bishop)
{
    symbol = "♗";
}
Bishop::Bishop(Colour colour) noexcept : ChessPiece(colour, bishop)
{
    symbol = (colour == white) ? "♗" : "♝";
}
bool Bishop::moveAllowed(Position positionStart, //
                         Position positionEnd) const noexcept
{
    if (!ChessPiece::differentSquare(positionStart, positionEnd))
        // move to same square
        return false;
    if (ChessPiece::diagonalMove(positionStart, positionEnd))
        return true;
    return false;
}
bool Bishop::takingMoveAllowed(Position positionStart, //
                               Position positionEnd) const noexcept
{
    return moveAllowed(positionStart, positionEnd); // no different taking move
}