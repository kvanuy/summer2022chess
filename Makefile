#######################################################################
# Project 1, Team 8 for EECS 22L, Spring 2022
#
# Initial author: LLLyyx
#
# Makefile: Makefile for PROJECT 1
#
#######################################################################

# Variables

# Default target

######################### Generate object files #######################

# Target for ChessGame.o
ChessGame.o: main.c Constants.h chess_piece_structure.h chess_board.h chess_move.h 
	gcc -Wall -std=c11 -c main.c -o ChessGame.o

# Target for gamestateflow.o
gamestateflow.o: gamestateflow.c gamestateflow.h
	gcc -Wall -std=c11 -c gamestateflow.c -o gamestateflow.o

# Target for AI.o
AI.o: AI.c AI.h
	gcc -Wall -std=c11 -c AI.c -o AI.o

# Target for chess_board.o
chess_board.o: chess_board.c chess_board.h Constants.h chess_piece_structure.h
	gcc -Wall -std=c11 -c chess_board.c -o chess_board.o

# Target for chess_move.o
chess_move.o: chess_move.c chess_board.h Constants.h chess_piece_structure.h
	gcc -Wall -std=c11 -c chess_move.c -o chess_move.o

# Target for ChessGame
ChessGame: chess_board.o ChessGame.o AI.o chess_move.o logfile.o gamestateflow.o
	gcc -Wall -std=c11 chess_board.o AI.o gamestateflow.o logfile.o chess_move.o ChessGame.o -o ChessGame

test: chess_board.o test.o AI.o chess_move.o gamestateflow.o
	gcc -Wall -std=c11 chess_board.o AI.o gamestateflow.o chess_move.o test.o -o Chesstest

test.o: test.c Constants.h chess_piece_structure.h chess_board.h chess_move.h
	gcc -Wall -std=c11 -c test.c -o test.o


#target for logfile.o
logfile.o: logfile.c logfile.h
	gcc -Wall -g -std=c11 -c logfile.c -o logfile.o

clean:
	rm -f *.o
	rm -f ChessGame
