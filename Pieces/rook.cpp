/*
File: rook.cpp
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: cpp file for the rook for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "../Position/position.h"
#include "chessPiece.h"
#include "rook.h"
#include <string>

Rook::Rook() noexcept : ChessPiece(rook)
{
    symbol = "♖";
}
Rook::Rook(Colour colour) noexcept : ChessPiece(colour, rook)
{
    symbol = (colour == white) ? "♖" : "♜";
}
bool Rook::moveAllowed(Position positionStart, //
                       Position positionEnd) const noexcept
{

    if (!ChessPiece::differentSquare(positionStart, positionEnd))
        return false;
    if (ChessPiece::straightMove(positionStart, positionEnd))
        return true;
    return false;
}
bool Rook::takingMoveAllowed(Position positionStart,              //
                             Position positionEnd) const noexcept //
{
    return moveAllowed(positionStart, positionEnd); // no different taking move
}
