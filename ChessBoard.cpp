/*
File: chessBoard.cpp
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: cpp file for the chessBoard for chess simulator
                coursework submission. The assignment is to program an
                chess engine in c++.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include "Position/position.h"
#include "Pieces/king.h"
#include "Pieces/queen.h"
#include "Pieces/bishop.h"
#include "Pieces/knight.h"
#include "Pieces/rook.h"
#include "Pieces/pawn.h"
#include "Pieces/chessPiece.h"
#include "ChessBoard.h"
#include <typeinfo>
#include <cmath>
#include <iostream>
#include <string>

//------------------------------------------------------------------------------
//------------------------------------PUBLIC------------------------------------
//------------------------------------------------------------------------------

ChessBoard::ChessBoard() noexcept { setup(); }

ChessBoard::~ChessBoard() noexcept { clear(); }

ChessBoard::ChessBoard(ChessBoard &other) noexcept { *this = other; }

ChessBoard &ChessBoard::operator=(ChessBoard const &other) noexcept
{
    if (this == &other)
        return *this;
    setup();
    clear();
    for (int row = 0; row < BOARD_ROWS; row++)
    {
        for (int column = 0; column < BOARD_COLUMNS; column++)
        {
            ChessPiece *otherPiecePtr = other.board[column][row];
            switch (otherPiecePtr->getType())
            // not use copy function - deep copy
            {
            case king:
                board[column][row] = new King(otherPiecePtr->getColour());
                break;
            case queen:
                board[column][row] = new Queen(otherPiecePtr->getColour());
                break;
            case bishop:
                board[column][row] = new Bishop(otherPiecePtr->getColour());
                break;
            case rook:
                board[column][row] = new Rook(otherPiecePtr->getColour());
                break;
            case knight:
                board[column][row] = new Knight(otherPiecePtr->getColour());
                break;
            case pawn:
                board[column][row] = new Pawn(otherPiecePtr->getColour());
                break;
            default:
                std::cerr << "Invalid type: = failed";
                break;
            }
        }
    }
    return *this;
}

void ChessBoard::print() const noexcept
{
    std::cout << "\n\n";
    std::cout << "-----------------------------------------\n";
    // iterate rows backwards for correct orientation
    for (int i = BOARD_ROWS - 1; i >= 0; --i)
    {
        std::cout << "| ";
        // iterate columns
        for (int j = 0; j < BOARD_COLUMNS; j++)
        {
            if (board[i][j] == nullptr)
                std::cout << "   | ";
            else
                std::cout << board[i][j]->getSymbol() << "  | ";
        }
        std::cout << std::endl;
        std::cout << "-----------------------------------------\n";
    }
    std::cout << "\n\n";
}

void ChessBoard::submitMove(std::string const start, //
                            std::string const end) noexcept
{
    // check if game has already ended without heavy recalculation
    if (gameOver)
    {
        std::cout << "Game over: reset to play again\n";
        return;
    }
    try
    {
        // work with virtual board as move is trialed
        copyBoard(board, virtualBoard);
        auto positionStart = Position(start); // set position format for defense
        auto positionEnd = Position(end);
        ChessPiece *piecePtr = getPiece(positionStart); // read loactions
        ChessPiece *targetPiecePtr = getPiece(positionEnd);
        if (!checkTurn(positionStart)) // check it is correct turn
            return;
        // check for enpassent/carry out if valid
        if (!enPassent(positionStart, positionEnd) //
            && !castle(positionStart, positionEnd))
        {
            if (moveValid(positionStart, positionEnd))
            // check if move valid
            {
                if (isKing(positionEnd)) // check not taking king
                {
                    std::cout << "Invalid move: cannot take a King";
                    return;
                }
                makeMove(positionStart, positionEnd); // make move on virtual
            }
            else
            {
                std::cout << "Invalid move\n";
                return;
            }
        }
        copyBoard(virtualBoard, board);
        // copy virtual board to game board
        printMove(piecePtr, targetPiecePtr, start, end); // print move text
        print();
        if (isGameOver())
        {
            gameOver = true;
            return;
        }
        changeTurn(); // switch turns
    }
    catch (int num) // catch errors from position stuff throughout code
    {
        return; // just terminate move, accept next
    }
}

void ChessBoard::resetBoard() noexcept
{
    turn = white; // reset variables
    gameOver = false;
    clear(); // reset board
    setup();
}

//------------------------------------------------------------------------------
//-----------------------------------SET BOARD----------------------------------
//------------------------------------------------------------------------------

void ChessBoard::clear() noexcept
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLUMNS; j++)
            delete board[i][j]; // delete all items from the board
    }
}

void ChessBoard::setup() noexcept
{
    int rows[2] = {0, 7}; // pawn rows
    Colour colours[2] = {white, black};
    for (int i = 0; i < BOARD_ROWS; i++) // set board to empty
    {
        for (int j = 0; j < BOARD_COLUMNS; j++)
            board[i][j] = nullptr;
    }
    for (int i = 0; i < BOARD_COLUMNS; i++) // intitialise pawns on board
    {
        board[1][i] = new Pawn(white);
        board[6][i] = new Pawn(black);
    }
    for (int i = 0; i < 2; i++) // initialise all other pieces
    {
        board[rows[i]][4] = new King(colours[i]);
        board[rows[i]][3] = new Queen(colours[i]);
        board[rows[i]][2] = new Bishop(colours[i]);
        board[rows[i]][5] = new Bishop(colours[i]);
        board[rows[i]][1] = new Knight(colours[i]);
        board[rows[i]][6] = new Knight(colours[i]);
        board[rows[i]][0] = new Rook(colours[i]);
        board[rows[i]][7] = new Rook(colours[i]);
    }
    std::cout << "A new chess game is started!\n";
}

//------------------------------------------------------------------------------
//---------------------------------GENERAL TOOLS--------------------------------
//------------------------------------------------------------------------------

ChessPiece *ChessBoard::getPiece(Position const position) const noexcept
{
    return board[position.getRow() - 1][position.getColumn() - 1];
}

ChessPiece *ChessBoard::getPiece(Position const position, //
                                 ChessPiece *other[8][8]) const noexcept
{
    return other[position.getRow() - 1][position.getColumn() - 1];
}

void ChessBoard::setPiece(Position const position, ChessPiece *piece) noexcept
{
    board[position.getRow() - 1][position.getColumn() - 1] = piece;
}

void ChessBoard::setPiece(Position const position, ChessPiece *piece, //
                          ChessPiece *other[8][8]) const noexcept
{
    other[position.getRow() - 1][position.getColumn() - 1] = piece;
}

bool ChessBoard::isKing(Position const position) const noexcept
{
    ChessPiece *testPiecePtr = getPiece(position, virtualBoard); // read place
    if (testPiecePtr != nullptr)
    // check there is a piece there
    {
        if (testPiecePtr->getType() == king) // check if king
            return true;
    }
    return false;
}

void ChessBoard::changeTurn() noexcept
{
    turn = Colour(-turn); // simple switch
}

bool ChessBoard::checkTurn(Position const positionStart) const noexcept
{
    ChessPiece *piecePtr = getPiece(positionStart); // read piece
    if (piecePtr == nullptr)                        // check piece in square
    {
        std::cout << "No piece at ";
        positionStart.print();
        return false;
    }
    if (piecePtr->getColour() != turn) // check turn
    {
        std::cout << "Invalid move: it is "
                  << ((turn == white) ? "white" : "black") << "'s turn.\n";
        return false;
    }
    return true;
}

void ChessBoard::makeMove(Position const positionStart, //
                          Position const positionEnd) noexcept
{
    ChessPiece *piecePtr = getPiece(positionStart, virtualBoard); // read piece
    ChessPiece *targetPiecePtr = getPiece(positionEnd, virtualBoard);
    delete targetPiecePtr; // make move
    setPiece(positionStart, nullptr, virtualBoard);
    setPiece(positionEnd, piecePtr, virtualBoard);
    piecePtr->moved();                    // mark move in piece
    lastPieceMoved = piecePtr;            // record last piece moved
    if (checkPawnConversion(positionEnd)) // check pawn conversion
        convertPawn(positionEnd);
}

void ChessBoard::printMove(ChessPiece const *piecePtr,       //
                           ChessPiece const *targetPiecePtr, //
                           std::string const start,          //
                           std::string const end) const noexcept
{
    std::cout << ((turn == white) ? "White's " : "Black's ")
              << piecePtr->getName() << " moves from "
              << start << " to " << end;
    if (targetPiecePtr != nullptr) // if a taking move
        std::cout << " taking " << ((turn == white) ? "Black's " : "White's ")
                  << targetPiecePtr->getName();
    std::cout << std::endl;
}

void ChessBoard::copyBoard(ChessPiece *const sourceBoard[8][8], //
                           ChessPiece *boardCopy[8][8]) const noexcept
{
    for (int i = 0; i < BOARD_ROWS; i++) // iterate rows
    {
        for (int j = 0; j < BOARD_COLUMNS; j++) // iterate columns
        {
            boardCopy[i][j] = sourceBoard[i][j];
            // copy all items from the board
        }
    }
}
//------------------------------------------------------------------------------
//----------------------------------MOVE CHECK----------------------------------
//------------------------------------------------------------------------------

bool ChessBoard::moveValid(Position const positionStart, //
                           Position const positionEnd) const
{
    ChessPiece *piecePtr = getPiece(positionStart, virtualBoard);
    // check the move doesn't leave king in check
    if (inCheckAfterMove(positionStart, positionEnd))
        return false;
    // check piece can make the movement
    return checkMotion(positionStart, positionEnd);
}

bool ChessBoard::checkObstructions(Position const positionStart, //
                                   Position const positionEnd) const
{
    ChessPiece *piecePtr = getPiece(positionStart, virtualBoard);
    // knights don't need to worry about obstructions
    if (piecePtr->getType() != knight)
    {
        Position tempPos = positionStart;
        int dirVec[2] = {0}, columnDif, rowDif;
        columnDif = positionEnd.getColumn() - positionStart.getColumn();
        rowDif = positionEnd.getRow() - positionStart.getRow();
        if (columnDif != 0)
            dirVec[0] = columnDif / std::abs(columnDif); // vertical direction
        if (rowDif != 0)
            dirVec[1] = rowDif / std::abs(rowDif); // horizontal direction
        tempPos = (tempPos + dirVec);              // temporary iterator
        while (tempPos != positionEnd)
        // if the target hasn't been reached
        {
            if (getPiece(tempPos, virtualBoard) != nullptr)
                // check for piece at square
                return true;
            tempPos = (tempPos + dirVec); // iterate forward
        }
    }
    return false;
}

bool ChessBoard::checkMotion(Position const positionStart, //
                             Position const positionEnd,   //
                             bool takingOveride) const
// takingOverride for inCheck tests
{
    ChessPiece *piecePtr = getPiece(positionStart, virtualBoard),
               *targetPiecePtr = getPiece(positionEnd, virtualBoard);
    if (targetPiecePtr != nullptr || takingOveride)
    // check if piece at target square
    {
        if (!piecePtr->takingMoveAllowed(positionStart, positionEnd))
            // check if move allowed
            return false;
        if (targetPiecePtr != nullptr //
            && targetPiecePtr->getColour() == piecePtr->getColour())
            // check not taking own piece
            return false;
    }
    else if (!piecePtr->moveAllowed(positionStart, positionEnd))
        // check move allowed by piece
        return false;
    if (checkObstructions(positionStart, positionEnd))
        // check for obstructions
        return false;
    return true;
}

bool ChessBoard::inCheckAfterMove(Position const positionStart, //
                                  Position const positionEnd) const
{
    bool result = false;
    ChessPiece *piecePtr = getPiece(positionStart, virtualBoard); // read
    ChessPiece *targetPiecePtr = getPiece(positionEnd, virtualBoard);
    setPiece(positionStart, nullptr, virtualBoard); // make moves
    setPiece(positionEnd, piecePtr, virtualBoard);  // on virtual board
    if (piecePtr == nullptr)
        return false;
    for (int row = 1; row <= BOARD_ROWS; row++) // search for kings
    {
        for (int column = 1; column <= BOARD_COLUMNS; column++)
        {
            auto testPosition = Position(column, row);
            if (isKing(testPosition)) // test if king
            {
                ChessPiece *king = getPiece(testPosition, virtualBoard);
                if (king->getColour() == piecePtr->getColour() && //
                    kingInCheck(testPosition))
                    // check for check
                    result = true;
            }
        }
    }
    setPiece(positionStart, piecePtr, virtualBoard); // reset board to initial
    setPiece(positionEnd, targetPiecePtr, virtualBoard);
    return result;
}

//------------------------------------------------------------------------------
//----------------------------------GAME STATE----------------------------------
//------------------------------------------------------------------------------

bool ChessBoard::isGameOver() const
{
    for (int row = 1; row <= BOARD_ROWS; row++) // search for kings
    {
        for (int column = 1; column <= BOARD_COLUMNS; column++)
        {
            auto testPosition = Position(column, row);
            if (isKing(testPosition) && kingInCheck(testPosition))
            {
                if (checkStaleMate())
                {
                    // checkmate is stalemate with check
                    std::cout << ((turn == 1) ? "Black" : "White")
                              << " is in checkmate\n";
                    return true;
                }
                // just in check
                std::cout << ((turn == 1) ? "Black" : "White")
                          << " is in check\n";
                return false;
            }
        }
    }
    if (checkStaleMate())
    // stalemate catcher
    {
        std::cout << "Stalemate: no-one wins!\n";
        return true;
    }
    return false;
}

bool ChessBoard::checkStaleMate() const
{
    int whiteMoves = 0, blackMoves = 0;
    // counters for piece with valid moves
    for (int row = 1; row <= BOARD_ROWS; row++) // iterate rows
    {
        for (int column = 1; column <= BOARD_COLUMNS; column++)
        // iterate columns
        {
            auto testPosition = Position(column, row);
            ChessPiece *piecePtr = getPiece(testPosition, virtualBoard);
            if (piecePtr != nullptr && anyValidMoves(testPosition))
            // check piece there
            {
                if (piecePtr->getColour() == white)
                    whiteMoves++; // count independently
                else
                    blackMoves++;
            }
        }
    }
    if ((blackMoves == 0 && turn == white) //
        || (whiteMoves == 0 && turn == black))
        // if either side cannot move
        return true;
    return false;
}

bool ChessBoard::kingInCheck(Position const position) const
// structured like this so that can be used for king moving into check
{
    ChessPiece *king = getPiece(position, virtualBoard);
    if (!isKing(position))
        return false;
    for (int row = 1; row <= BOARD_ROWS; row++) // iterate over rows
    {
        for (int column = 1; column <= BOARD_COLUMNS; column++)
        // iterate over columns
        {
            auto testPosition = Position(column, row);
            if (testPosition != position)
            // don't check square king is taking
            {
                ChessPiece *testPiecePtr = getPiece(testPosition, virtualBoard);
                // get piece at square
                if (testPiecePtr != nullptr
                    // check if piece at target square
                    && testPiecePtr->getColour() != king->getColour()
                    // check opposition
                    && checkMotion(testPosition, position, true))
                    // see if valid move
                    // takingOverride = true for pawns checking king
                    return true;
            }
        }
    }
    return false;
}

bool ChessBoard::anyValidMoves(Position const position) const
{
    for (int targetRow = 1; targetRow <= BOARD_ROWS; targetRow++)
    // iterate move locations
    {
        for (int targetColumn = 1; targetColumn <= BOARD_COLUMNS; //
             targetColumn++)
        // iterate move locations
        {
            if (moveValid(position, {targetColumn, targetRow}))
                // if valid move
                return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------
//---------------------------------SPECIAL MOVES--------------------------------
//------------------------------------------------------------------------------

bool ChessBoard::castle(Position const positionStart, //
                        Position const positionEnd)
{
    ChessPiece *kingPtr = getPiece(positionStart, virtualBoard), *rookPtr;
    int column = positionEnd.getColumn(), row = positionEnd.getRow(), //
        longCastleColumn = 3, shortCastleColumn = 7;
    auto emptySquare = Position(2, row),  // long castle empty square
        rookSource = Position(1, 1),      //
        rookDestination = Position(1, 1); // place holder positions
    if (isKing(positionStart)
        // check is king
        && kingPtr->getNumMoves() == 0
        // this move was a kings first move
        && !kingInCheck(positionStart)
        // king cannot castle out of check
    )
    {
        if ((kingPtr->getColour() == white && row == 1) //
            || (kingPtr->getColour() == black && row == BOARD_ROWS))
        // check that king remains in home row
        {
            if (column == longCastleColumn                         // long
                && getPiece(emptySquare, virtualBoard) == nullptr) // castle
            // long castle has extra, empty square to check
            {
                rookSource = Position(1, row);
                rookPtr = getPiece(rookSource, virtualBoard);
                rookDestination = Position(4, row);
            }
            else if (column == shortCastleColumn) // short castle
            {
                rookSource = Position(BOARD_COLUMNS, row);
                rookPtr = getPiece(rookSource, virtualBoard);
                rookDestination = Position(6, row);
            }
            else
                return false;
            if (rookPtr != nullptr &&
                // square not empty
                rookPtr->getNumMoves() == 0
                // unmoved rook there
                && getPiece(positionEnd, virtualBoard) == nullptr     //
                && getPiece(rookDestination, virtualBoard) == nullptr //
                && !inCheckAfterMove(positionStart, rookDestination)
                // cannot move through check
                && !inCheckAfterMove(positionStart, positionEnd)
                // cannot move to check(don't need to worry about rook here)
            )
            {
                setPiece(positionStart, nullptr, virtualBoard);
                setPiece(rookSource, nullptr, virtualBoard);
                setPiece(rookDestination, rookPtr, virtualBoard);
                setPiece(positionEnd, kingPtr, virtualBoard);
                kingPtr->moved(); // record move in piece
                rookPtr->moved();
                lastPieceMoved = kingPtr; // record last moved piece
                return true;
            }
        }
    }

    return false;
}

bool ChessBoard::checkPawnConversion(Position const position) const noexcept
{
    ChessPiece *piecePtr = getPiece(position, virtualBoard);
    if (piecePtr->getType() == pawn)
    {
        // if at the end of board
        if (piecePtr->getColour() == white && position.getRow() == BOARD_ROWS)
            return true;
        if (piecePtr->getColour() == black && position.getRow() == 1)
            return true;
    }
    return false;
}

void ChessBoard::convertPawn(Position const position) noexcept
{
    ChessPiece *piecePtr = getPiece(position, virtualBoard), *newPiecePtr;
    Colour colour = piecePtr->getColour();
    char type;
    delete piecePtr; // delete pawn option
    std::cout << "Select pawn conversion (Q/B/R/K): ";
    std::cin.get(type);
    // take piece specification
    while (type != 'Q' && type != 'B' && type != 'R' && type != 'K')
    {
        std::cout << "invalid character\n";
        std::cout << "Select pawn conversion (Q/B/R/K): ";
        std::cin.get(type);
    }
    switch (type)
    {
    case 'Q':
        newPiecePtr = new Queen(colour);
        break;
    case 'B':
        newPiecePtr = new Bishop(colour);
        break;
    case 'R':
        newPiecePtr = new Rook(colour);
        break;
    case 'K':
        newPiecePtr = new Knight(colour);
        break;
    }
    setPiece(position, newPiecePtr); // set piece
}

bool ChessBoard::enPassent(Position const positionStart,
                           Position const positionEnd)
{
    ChessPiece *piecePtr = getPiece(positionStart, virtualBoard);
    // direction vector of target square relative to target piece
    int dirVec[2] = {0, piecePtr->getColour()}, midRows[] = {4,
                                                             5};
    if (piecePtr->getType() == pawn) // check piece is pawn
    {
        ChessPiece *targetPiecePtr = getPiece(positionEnd - dirVec, //
                                              virtualBoard);
        setPiece(positionEnd - dirVec, nullptr, virtualBoard);
        if (inCheckAfterMove(positionStart, positionEnd))
        {
            setPiece(positionEnd - dirVec, targetPiecePtr, virtualBoard);
            return false;
        }
        setPiece(positionEnd - dirVec, targetPiecePtr, virtualBoard);
        if ( // check piece exists
            targetPiecePtr != nullptr
            // check end square empty
            && getPiece(positionEnd) == nullptr
            // check target is pawn
            && targetPiecePtr->getType() == pawn
            // check target is other team
            && targetPiecePtr->getColour() != piecePtr->getColour()
            // check target has one move
            && targetPiecePtr->getNumMoves() == 1
            // check target just moved
            && targetPiecePtr == lastPieceMoved
            // check target performed correct move
            && ((positionEnd - dirVec).getRow() == midRows[0] //
                || (positionEnd - dirVec).getRow() == midRows[1]))
        {
            if ( // check piece and target on same row
                positionStart.getRow() == (positionEnd - dirVec).getRow()
                // check one column away
                && ((positionStart.getColumn() //
                     == (positionEnd - dirVec).getColumn() + 1) ||
                    (positionStart.getColumn() //
                     == (positionEnd - dirVec).getColumn() - 1))
                // check movement correct
                && piecePtr->takingMoveAllowed(positionStart, positionEnd))
            {
                delete targetPiecePtr;
                setPiece(positionEnd - dirVec, nullptr);
                setPiece(positionStart, nullptr);
                setPiece(positionEnd, piecePtr);
                piecePtr->moved();         // record move in piece
                lastPieceMoved = piecePtr; // record last moved piece
                return true;
            }
        }
    }
    return false;
}
