/*
File: chessBoard.h
Owner: Edward Jenks
Username: ej3718
Last edited: 14/12/21
Last editor: Edward Jenks
Description: h file for the chessBoard for chess simulator
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

#include <string>

class ChessBoard
{
    Colour turn = white;
    ChessPiece *board[8][8] = {}, *lastPieceMoved = nullptr;
    // i discussed making virtualBoard mutable with a TA and was told it was
    // ok in this case. the logic behind it is that as far as the user is
    // concerned, changes to the virtual board do not affect the game state,
    // so they don't violate constness as its just a means to test moves.
    // virtualBoard could be not mutable, but then most functions wouldn't
    // be const.
    mutable ChessPiece *virtualBoard[8][8] = {};
    bool gameOver = false;
    // moves are tested on virtual board before being tested on the game board
    // constness ensures game board is not altered until move validated

    //-----------------------------------SET BOARD------------------------------
    // function to clear the game board
    // precondition: game board array is full of a mix of nullptrs and
    //                  chess piece pointers
    // postcondition: all pieces in the board are deleted
    void clear() noexcept;
    // function to setup the game board
    // precondition: board initialised in any state
    // postcondition: board set up with chess starting layout
    void setup() noexcept;

    //---------------------------------GENERAL TOOLS----------------------------
    // function to get a piece from the game board
    // precondition: function passed the position of desired piece
    // postcondition: ptr to piece in position returned
    ChessPiece *getPiece(Position const position) const noexcept;
    // function to get a piece from the an other board
    // precondition: function passed the position of desired piece and board
    // postcondition: ptr to piece in position on board returned
    ChessPiece *getPiece(Position const position, //
                         ChessPiece *other[8][8]) const noexcept;
    // function to set a piece in the game board
    // precondition: function passed the position and piece ptr
    // postcondition: piece placed in board
    void setPiece(Position const position, ChessPiece *piece) noexcept;
    // function to set a piece in an other board
    // precondition: function passed the position and piece ptr
    // postcondition: piece placed in other board
    void setPiece(Position const position, ChessPiece *piece, //
                  ChessPiece *other[8][8]) const noexcept;
    // function to check if a piece is king
    // precondition: function passed position of a piece
    // postcondition: return true if king
    bool isKing(Position const position) const noexcept;
    // function to change the turn of the game
    // precondition:
    // postcondition: turn switched
    void changeTurn() noexcept;
    // function to check if it is a piece's turn
    // precondition: function passed the position of desired piece
    // postcondition: return true if it is pieces turn
    bool checkTurn(Position const positionStart) const noexcept;
    // function to make the move
    // precondition: start position and end position given to function
    // postcondition: piece moved, target pieces deleted
    void makeMove(Position const positionStart, //
                  Position const positionEnd) noexcept;
    // function to print text with move details
    // precondition: function passed piece pointers and positions
    // postcondition:
    void printMove(ChessPiece const *piecePtr, ChessPiece const *targetPiecePtr, //
                   std::string const start,                                      //
                   std::string const end) const noexcept;
    // function to copy one board to another
    // precondition: function passed a source and destination board
    // postcondition: pointers in board copied across - NOT A DEEP COPY
    //                  so deletes etc. work in both.
    void copyBoard(ChessPiece *const sourceBoard[8][8], //
                   ChessPiece *boardCopy[8][8]) const noexcept;

    //----------------------------------MOVE CHECK------------------------------
    // function check if a move is valid
    // precondition: function passed a start and end position
    // postcondition: returns true if move is valid
    bool moveValid(Position const positionStart, Position const positionEnd) //
        const;
    // function to check if there are any obstructions for a pieces move
    // precondition: functions passed start and end position
    // postcondition: return true if there is an obstruction to the piece
    bool checkObstructions(Position const positionStart, //
                           Position const positionEnd) const;
    // function to check if the motion (move pattern/obstruction)
    // of the piece is allowed
    // precondition: functions passed start and end position and a 'taking
    //                  override' to consider the move a taking move regardless
    //                  of destination.
    // postcondition: return true if motion is allowed
    bool checkMotion(Position const positionStart, Position const positionEnd, //
                     bool const takingOveride = false) const;
    // function to check if a move leaves activeplayer in check
    // precondition: function passed a start and end position
    // postcondition: returns true if left in check
    bool inCheckAfterMove(Position const positionStart, //
                          Position const positionEnd) const;

    //----------------------------------GAME STATE------------------------------
    // function check if the game is over
    // precondition:
    // postcondition: returns true ifgame is over
    bool isGameOver() const;
    // function check if in stale mate
    // precondition:
    // postcondition: returns true if stalemate
    bool checkStaleMate() const;
    // function check if a king is checked
    // precondition: function passed the position of a king
    // postcondition: returns true if king is in check
    bool kingInCheck(Position const positionEnd) const;
    // function check if a piece has any valid moves
    // precondition: function passed position of piece
    // postcondition: returns true if there is a valid move
    bool anyValidMoves(Position position) const;

    //---------------------------------SPECIAL MOVES----------------------------
    // function to carry out a castle if possible
    // precondition: function passed a start and end position
    // postcondition: returns true if possible and does castle
    bool castle(Position const positionStart, //
                Position const positionEnd);
    // function to check if a pawn can be converted
    // precondition: function passed a position of pawn
    // postcondition: if at end of board return true
    bool checkPawnConversion(Position const position) const noexcept;
    // function to provide pawn conversion
    // precondition: function passed a position of pawn
    // postcondition: pawn is converted to desied piece
    void convertPawn(Position const position) noexcept;
    // function to check for and carry out en passent
    // precondition: function passed a start and end position
    // postcondition: enpassent is checked and carried out if applicable
    bool enPassent(Position const positionStart, //
                   Position const positionEnd);

public:
    //------------------------------------PUBLIC--------------------------------
    ChessBoard() noexcept;
    ChessBoard(ChessBoard &other) noexcept;
    ChessBoard &operator=(ChessBoard const &other) noexcept;
    ~ChessBoard() noexcept;
    // function to print the board
    // precondition:
    // postcondition: game board printed with unicode symbols
    void print() const noexcept;
    // function make move
    // precondition: function passed a start and end position
    // postcondition: move made if allowed
    void submitMove(std::string const start, std::string const end) noexcept;
    // function to reset the board
    // precondition:
    // postcondition: all pieces are deleted and board returned to start
    void resetBoard() noexcept;
};