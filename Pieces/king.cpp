/*
File: king.cpp
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: cpp file for the king for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "../Position/position.h"
#include "chessPiece.h"
#include "king.h"
#include <cmath>
#include <string>

King::King() noexcept : ChessPiece(king)
{
    symbol = "♔";
}
King::King(Colour colour) noexcept : ChessPiece(colour, king)
{
    symbol = (colour == white) ? "♔" : "♚";
}
bool King::moveAllowed(Position positionStart, //
                       Position positionEnd) const noexcept
{
    int columnDif, rowDif;
    if (!ChessPiece::differentSquare(positionStart, positionEnd))
        return false;
    columnDif = std::abs(positionStart.getColumn() - positionEnd.getColumn());
    rowDif = std::abs(positionStart.getRow() - positionEnd.getRow());
    if ((columnDif == 1 || rowDif == 1) && columnDif < 2 && rowDif < 2)
        return true;
    return false;
}
bool King::takingMoveAllowed(Position positionStart,              //
                             Position positionEnd) const noexcept //
{
    return moveAllowed(positionStart, positionEnd); // no different taking move
}
