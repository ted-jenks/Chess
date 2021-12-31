/*
File: pawn.cpp
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: cpp file for the pawn for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "../Position/position.h"
#include "chessPiece.h"
#include "pawn.h"
#include <string>

Pawn::Pawn() noexcept : ChessPiece(pawn)
{
    symbol = "♙";
}
Pawn::Pawn(Colour colour) noexcept : ChessPiece(colour, pawn)
{
    symbol = (colour == white) ? "♙" : "♟︎";
}
bool Pawn::moveAllowed(Position positionStart, //
                       Position positionEnd) const noexcept
{
    int columnDif, rowDif;
    columnDif = std::abs(positionEnd.getColumn() - positionStart.getColumn());
    rowDif = positionEnd.getRow() - positionStart.getRow();
    if (!ChessPiece::differentSquare(positionStart, positionEnd))
        return false;
    if (numMoves == 0)
    {
        if ((rowDif == colour || rowDif == 2 * colour) && columnDif == 0)
            return true;
    }
    if (rowDif == colour && columnDif == 0)
        return true;
    return false;
}
bool Pawn::takingMoveAllowed(Position positionStart, //
                             Position positionEnd) const noexcept
{
    int columnDif;
    columnDif = std::abs(positionEnd.getColumn() - positionStart.getColumn());
    if (positionEnd.getRow() == positionStart.getRow() + colour //
        && columnDif == 1)
        return true;
    return false;
}
