# Chess

This repo contains the code from a university project where one had to build a chess simulator in C++. OOP concepts have been used to make the design flexible and elegant.

All pieces inherit from a base class which has a 'moveaAllowed' virtual function. For each piece, this contains the move pattern information. The game state is stored as an 8x8 array of pointers to chessPiece base class types. The correct move pattern/other piece info is returned by dynamic binding based on the piece in the square. 

The code was constructed to be run by a provided ChessMain.cpp script which outlined the key functions that the program had to have. The ChessMain.cpp provided here is similar, but contains moves that demonstrate en passent, castling, pawn conversion and handling of many illegal moves. 

A virtual board was used to test the legallity of certain moves before commiting them to the game board. I had a discussion with a teaching assistant over whether I should make the virtual board mutable or not. Since the virtual board is purely an internal structure that does not effect the state of the game as far as the user is concerned, we agreed it was appropriate to make it mutable. This allowed for move-checking functions to be const which added a layer of protection throughout the code and prevents the game-state being altered unintentionally. 

The code is setup to be run by a script which can be configured to take moves from user input, allowing for a live game between two people to be modeled. Care has been taken when considering edge cases, particularly with special moves, to make sure bugs aren't present.
