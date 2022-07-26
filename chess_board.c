#include "chess_board.h"

char ChessBoard [8][50];
char SplitLine[] = "    +----+----+----+----+----+----+----+----+";
char EndLine[] = "       a    b    c    d    e    f    g    h";
char chess[8][50];

void Chess_board_default(){
	strcpy(ChessBoard[0],"8   |    |    |    |    |    |    |    |    |");
  strcpy(ChessBoard[1],"7   |    |    |    |    |    |    |    |    |");
	strcpy(ChessBoard[2],"6   |    |    |    |    |    |    |    |    |");
	strcpy(ChessBoard[3],"5   |    |    |    |    |    |    |    |    |");
	strcpy(ChessBoard[4],"4   |    |    |    |    |    |    |    |    |");
	strcpy(ChessBoard[5],"3   |    |    |    |    |    |    |    |    |");
	strcpy(ChessBoard[6],"2   |    |    |    |    |    |    |    |    |");
	strcpy(ChessBoard[7],"1   |    |    |    |    |    |    |    |    |");
}

void Chess_pieces_default(){
	int iStart = 6, i = 0, j = 0, k = 0;
	char piecesName[64][3] = {"bR","bN","bB","bQ","bK","bB","bN","bR",
	                          "bP","bP","bP","bP","bP","bP","bP","bP",
	                          "  ","  ","  ","  ","  ","  ","  ","  ",
	                          "  ","  ","  ","  ","  ","  ","  ","  ",
	                          "  ","  ","  ","  ","  ","  ","  ","  ",
	                          "  ","  ","  ","  ","  ","  ","  ","  ",
							              "wP","wP","wP","wP","wP","wP","wP","wP",
						            	  "wR","wN","wB","wQ","wK","wB","wN","wR"};
	int iPointY[4]={0,1,6,7};
	for (j=0;j<8;++j){
		for (i=0; i<8; ++i){
			strcpy(Pieces[j*8+i].Name,piecesName[j*8+i]);
			if (j == 1){
				Pieces[j*8+i].Player.Color = BLACK;
				Pieces[j*8+i].TYPE = PAWN;
        Pieces[j*8+i].FirstMove = NOFIRSTMOVE;
				//test statements to see if pawn is assigned type
				//printf("%d",Pieces[j*8+i].TYPE + 3);

			}
			else if (j == 0){
				Pieces[j*8+i].Player.Color = BLACK;
				if (i == 0 || i == 7){Pieces[j*8+i].TYPE = ROOK;
                              Pieces[j*8+i].FirstMove = NOFIRSTMOVE;}
				if (i == 1 || i == 6){Pieces[j*8+i].TYPE = KNIGHT;}
				if (i == 2 || i == 5){Pieces[j*8+i].TYPE = BISHOP;}
				if (i == 3 ){Pieces[j*8+i].TYPE = QUEEN;}
				if (i == 4 ){Pieces[j*8+i].TYPE = KING;
                              Pieces[j*8+i].FirstMove = NOFIRSTMOVE;}
			}
			else if (j == 7){
				Pieces[j*8+i].Player.Color = WHITE;
				if (i == 0 || i == 7){Pieces[j*8+i].TYPE = ROOK;
                              Pieces[j*8+i].FirstMove = NOFIRSTMOVE;}
				if (i == 1 || i == 6){Pieces[j*8+i].TYPE = KNIGHT;}
				if (i == 2 || i == 5){Pieces[j*8+i].TYPE = BISHOP;}
				if (i == 3 ){Pieces[j*8+i].TYPE = QUEEN;}
				if (i == 4 ){Pieces[j*8+i].TYPE = KING;
                              Pieces[j*8+i].FirstMove = NOFIRSTMOVE;}
			}
			else if (j == 6){
				Pieces[j*8+i].Player.Color = WHITE;
				Pieces[j*8+i].TYPE = PAWN;
        Pieces[j*8+i].FirstMove = NOFIRSTMOVE;;
			}
      else{
        Pieces[j*8+i].TYPE = EMPTY;
        Pieces[j*8+i].Player.Color = DNE;
      }
			//Pieces[j*8+i].Position = j*8+1;
		}
	}
/*	for (k = 0; k < 64; ++k){
    	for(j = 0; j < 3; ++j){
        	printf("%c",board[k][j]);
    	}
    	printf("\n");
	}*/
}

void Get_board(){
	int i,j;
	for (i=0;i<8;++i){
		strcpy(chess[i],ChessBoard[i]);
	}
	for (j=0;j<8;++j){
		for (i=0;i<8;++i){
			chess[j][6+5*i] = Pieces[j*8+i].Name[0];
			chess[j][7+5*i] = Pieces[j*8+i].Name[1];
		}
	}
}

void Print_board(){
	system("clear");
	int i;
	for (i=0; i<8; ++i){
		printf("%s\n",SplitLine);
		printf("%s\n",chess[i]);
	}
	printf("%s\n",SplitLine);
	printf("%s\n",EndLine);
	//system("pause");
}

void Clean_board(){
	//system("cls");
}
