#ifndef CHESS_PIECE_STRUCTURE_H
#define CHESS_PIECE_STRUCTURE_H
#include "Constants.h"

typedef struct Chess_moveList Chess_moveList;
typedef struct Chess_move Chess_move;
typedef struct Chess_position Chess_position;
typedef struct Board Chess_board;
typedef struct Chess_player Chess_player;
typedef struct Chess_piece Chess_piece;

int enpassant_risk_pawn_location;

typedef enum {
	EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
}Chess_piece_type;

typedef enum {
	BLACK, WHITE, DNE
}Chess_player_color;

typedef enum {
	Player1, Player2, AI, BLANK
}Chess_player_type;

// added for special moves

typedef enum {
	NOFIRSTMOVE, FIRST, NA
}Chess_piece_movestatus;

struct Chess_moveList{
	unsigned int 		Length;
	Chess_move 			*First;
	Chess_move 			*Last;
};

struct Chess_move{
	Chess_moveList		*List;
	Chess_move			*Next;
	Chess_move			*Prev;
	int					index;
	Chess_piece			*Piece;
	Chess_position		*Cur_position;
	Chess_position	 	*New_position;
	int 					points;
};

struct Chess_position{
	//UPDATE -COMMENTING THESE 2 OUT
	//Chess_board			*Board;
	//Chess_piece			*Piece;
	int 				Position;
};

struct Board{
  	Chess_position		Board[ROW][COL];
  	Chess_player		*PlayerA;
  	Chess_player		*PlayerB;
};

struct Chess_player{
	Chess_player_color	Color;
	Chess_player_type	Player;
};

struct Chess_piece{
	char				Name[2];
	Chess_piece_type	TYPE;
	Chess_position		*Position;
	Chess_player		Player;
	Chess_piece_movestatus	FirstMove;
}Pieces[64];

#endif
