/*
File: king.h
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: h file for the king for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "chessPiece.h"

#ifndef KING_H
#define KING_H

// castling
class King : public ChessPiece
{
public:
    King() noexcept;
    King(Colour colour) noexcept;

    // override function to check if the movement can be made
    // precondition: function passed a start and end position
    // postcondition: return true if allowed
    bool moveAllowed(Position positionStart, //
                     Position positionEnd) const noexcept override;
    // override function to check if the movement can be made when taking
    // precondition: function passed a start and end position
    // postcondition: return true if allowed
    bool takingMoveAllowed(Position positionStart, //
                           Position positionEnd) const noexcept override;
};

#endif