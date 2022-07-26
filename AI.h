//Header file for Ai.h
#ifndef AI_H
#define AI_H
#include "chess_move.h"
#include "Constants.h"
#include "chess_piece_structure.h"

void AIMove();
void JungKook();

/* Create a new list of moves */
Chess_moveList *CreateMoveList(void);

/* Delete a list of moves and all entries */
void DeleteMoveList(Chess_moveList *List);

/* create a new move entry */
static Chess_move *NewMoveEntry(unsigned int Cur_Position, unsigned int New_Position);

/* Insert a move to the move list at the end */
void AppendMove(Chess_moveList *List, unsigned int Cur_Position, unsigned int New_Position);

/* Delete a move to the move list at the end */
//static Chess_position DeleteMove(Chess_move *Chess_Move);

// checkmate
int checkmate(int check, int color);

//send current position of final move
//int sendCurPos();

//send new position of final move
//int sendNewPos();

#endif
