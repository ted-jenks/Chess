/*
File: position.cpp
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: cpp file for the position struct for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "position.h"
#include <iostream>

Position::Position(int inColumn, int inRow)
{
    if (inRow > 0 && inRow <= BOARD_ROWS && inColumn > 0 && inColumn <= BOARD_COLUMNS)
    {
        this->row = inRow;
        this->column = inColumn;
    }
    else
    {
        std::cerr << "Invalid position: must be within board bounds\n";
        throw 1;
    }
}
Position::Position(std::string pos) //
    : Position(static_cast<int>(pos[0]) - 'A' + 1, pos[1] - '0')
{
    if (pos.length() > 2 || pos.length() < 2)
    {
        std::cerr << "Invalid position: incorrect number of arguments\n";
        throw 1;
    }
}
Position::Position(char column, int row) //
    : Position(static_cast<int>(column) - 'A' + 1, row)
{
}
int Position::getRow() const noexcept { return row; }
void Position::setRow(int newRow)
{
    if (newRow > 0 && newRow <= BOARD_ROWS)
    {
        row = newRow;
    }
    else
    {
        std::cerr << "Invalid position: must be within board bounds\n";
        throw 1;
    }
}
int Position::getColumn() const noexcept { return column; }
void Position::setColumn(int newColumn)
{
    if (newColumn > 0 && newColumn <= BOARD_COLUMNS)
    {
        column = newColumn;
    }
    else
    {
        std::cerr << "Invalid position: must be within board bounds\n";
        throw 1;
    }
}
void Position::print() const noexcept
{
    char charColumn = static_cast<char>(column + 'A' - 1);
    std::cout << charColumn << " " << row << std::endl;
}
bool Position::operator==(const Position &other) noexcept //
{
    return (this->row == other.row && this->column == other.column);
}
bool Position::operator!=(const Position &other) noexcept //
{
    return !(*this == other);
}
Position Position::operator+(int const other[2]) const //
{
    return Position(column + other[0], row + other[1]);
}
Position Position::operator-(int const other[2]) const //
{
    return Position(column - other[0], row - other[1]);
}
Position Position::operator+(Position const other) const //
{
    return Position(column + other.column, row + other.row);
}
Position Position::operator-(Position const other) const //
{
    return Position(column - other.column, row - other.row);
}