/*
File: knight.cpp
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: cpp file for the knight for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "../Position/position.h"
#include "chessPiece.h"
#include "knight.h"
#include <cmath>
#include <string>

Knight::Knight() noexcept : ChessPiece(knight)
{
    symbol = "♘";
}
Knight::Knight(Colour colour) noexcept : ChessPiece(colour, knight)
{
    symbol = (colour == white) ? "♘" : "♞";
}
bool Knight::moveAllowed(Position positionStart, //
                         Position positionEnd) const noexcept
{
    int columnDif, rowDif;
    if (!ChessPiece::differentSquare(positionStart, positionEnd))
        return false;
    columnDif = std::abs(positionStart.getColumn() - positionEnd.getColumn());
    rowDif = std::abs(positionStart.getRow() - positionEnd.getRow());
    if (columnDif == 2 && rowDif == 1)
        return true;
    if (rowDif == 2 && columnDif == 1)
        return true;
    return false;
}
bool Knight::takingMoveAllowed(Position positionStart, //
                               Position positionEnd) const noexcept
{
    return moveAllowed(positionStart, positionEnd); // no different taking move
}
