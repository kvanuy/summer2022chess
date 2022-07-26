#include "chess_move.h"
#include "gamestateflow.h"
#include "AI.h"
#include "logfile.h"





int main(){

	const char* pieceNames[7] = {"EMPTY", "PAWN", "ROOK", "KNIGHT","BISHOP","QUEEN","KING"};
	const char* Colors[3] = {"BLACK", "WHITE", "DNE"};
	int i, j;

	Chess_board_default();
	Chess_pieces_default();
	Get_board();
	Print_board();




  for (i=0; i<64; i++) {
	  printf(" Type: %s, color: %s, firstmove: %d, index: %d \n", pieceNames[Pieces[i].TYPE], Colors[Pieces[i].Player.Color], Pieces[i].FirstMove, i);
    for (j=0; j<64; j++){
      CheckMove(i,j, 0);
      if (CheckMove(i,j,0) == 1){
     	   printf("\n newpos j : %d", j);
         printf("  legal  ");
              }
            }
         }
 return 0;}