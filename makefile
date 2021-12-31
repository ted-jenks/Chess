CC=g++
CFLAGS=-g -Wall

_DEPS = Position/position.h chessBoard.h Pieces/chessPiece.h Pieces/king.h Pieces/queen.h Pieces/bishop.h Pieces/knight.h Pieces/rook.h Pieces/pawn.h
DEPS = $(patsubst %,%,$(_DEPS))

_OBJ = ChessMain.o ChessBoard.o Position/position.o Pieces/chessPiece.o Pieces/king.o Pieces/queen.o Pieces/bishop.o Pieces/knight.o Pieces/rook.o Pieces/pawn.o
OBJ = $(patsubst %,%,$(_OBJ))

SUBDIR_ROOTS := Position Pieces
DIRS := . $(shell find $(SUBDIR_ROOTS) -type d)
GARBAGE_PATTERNS := *.o *~ core *~
GARBAGE := $(foreach DIR,$(DIRS),$(addprefix $(DIR)/,$(GARBAGE_PATTERNS)))

chess: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean

clean:
	rm -rf $(GARBAGE) chess
