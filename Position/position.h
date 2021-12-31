/*
File: position.h
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: h file for the position struct for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include <string>
#ifndef POSITION_H
#define POSITION_H

int const BOARD_ROWS = 8;
int const BOARD_COLUMNS = 8;

// struct to hold position data
struct Position
{
    // not possible to create an invalid position
    Position(int inColumn, int inRow);
    Position(std::string pos);
    Position(char column, int row);
    // function to get the row
    // precondition:
    // postcondition: return row
    int getRow() const noexcept;
    // function to set row
    // precondition: function passed desired row
    // postcondition: row set if allowed
    void setRow(int newRow);
    // function to get the column
    // precondition:
    // postcondition: return column
    int getColumn() const noexcept;
    // function to set column
    // precondition: function passed desired column
    // postcondition: column set if allowed
    void setColumn(int newColumn);
    // function to print the position
    // precondition:
    // postcondition: print position
    void print() const noexcept;

    // operator overloading for ease
    bool operator==(const Position &other) noexcept;
    bool operator!=(const Position &other) noexcept;
    Position operator+(int const other[2]) const;
    Position operator-(int const other[2]) const;
    Position operator+(Position const other) const;
    Position operator-(Position const other) const;

private:
    int row;
    int column;
};

#endif