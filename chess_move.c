#include "chess_move.h"
#include <stdlib.h>

 //changed "s" to ' ' - hard coded
//char s[6] = "|    |";


void Move_Piece(int Cur_Position, int New_Position) {
  //what this does is that it moves each letter of the piece to the new location
  //for example, lets say you want to move queen bQ. What it does is that it moves
  //the letter b and the letter Q to a square
  Pieces[New_Position].Name[0] = Pieces[Cur_Position].Name[0];
  Pieces[New_Position].Name[1] = Pieces[Cur_Position].Name[1];
  Pieces[Cur_Position].Name[0] = ' ';
  Pieces[Cur_Position].Name[1] = ' ';
  Pieces[New_Position].Player = Pieces[Cur_Position].Player;
  Pieces[Cur_Position].Player.Player = BLANK;
  Pieces[New_Position].Player.Color = Pieces[Cur_Position].Player.Color;
  Pieces[Cur_Position].Player.Color = DNE;
  Pieces[New_Position].TYPE = Pieces[Cur_Position].TYPE;
  Pieces[Cur_Position].TYPE = EMPTY;
  Pieces[New_Position].FirstMove = Pieces[Cur_Position].FirstMove;
  Pieces[Cur_Position].FirstMove = NA;
}

//special moves
void Castling(int New_Position){
	if (Pieces[New_Position].TYPE == KING && Pieces[New_Position].FirstMove == FIRST){
		// right castling update moving 2 pieces
		if (Pieces[New_Position+1].TYPE == ROOK && Pieces[New_Position+1].FirstMove == FIRST){
			Pieces[New_Position+1].FirstMove = NA; // deflagging rook
			Pieces[New_Position].FirstMove = NA; // deflagging king
			Move_Piece(New_Position+1, New_Position-1); // moving rook
			}
		// left castling update moving 2 pieces
		if (Pieces[New_Position-2].TYPE == ROOK && Pieces[New_Position-2].FirstMove == FIRST){
			Pieces[New_Position-2].FirstMove = NA; // deflag rook
			Pieces[New_Position].FirstMove = NA; // deflag king
			Move_Piece(New_Position-2, New_Position+1); // move rook
			}
      printf("Castling \n");
      }}

//en passant
int ENPASSANT(int enpassant_risk_pawn_location, int New_Position){

	if (Pieces[New_Position].TYPE == PAWN && Pieces[enpassant_risk_pawn_location].TYPE ==PAWN && Pieces[New_Position].FirstMove == NA){
		if ((Pieces[New_Position].Player.Color == BLACK && (New_Position-enpassant_risk_pawn_location ==8))||
		(Pieces[New_Position].Player.Color == WHITE && (New_Position-enpassant_risk_pawn_location==-8))){
				// remove piece
  Pieces[enpassant_risk_pawn_location].Name[0] = ' ';
  Pieces[enpassant_risk_pawn_location].Name[1] = ' ';
  Pieces[enpassant_risk_pawn_location].Player.Player = BLANK;
  Pieces[enpassant_risk_pawn_location].Player.Color = DNE;
  Pieces[enpassant_risk_pawn_location].TYPE = EMPTY;
  Pieces[enpassant_risk_pawn_location].FirstMove = NA;
			}
      printf("En Passant \n");
	return 0;
	}
	if (enpassant_risk_pawn_location != 0){
		Pieces[enpassant_risk_pawn_location].FirstMove = NA;
		}
	if (Pieces[New_Position].TYPE == PAWN && Pieces[New_Position].FirstMove == FIRST){
    return New_Position;}
    return 0;}


//promotion
	void Promotion(int New_Position, int mode){
		if (Pieces[New_Position].TYPE == PAWN && (((New_Position/8 == 7) && Pieces[New_Position].Player.Color == BLACK)||
			((New_Position/8 ==0) && Pieces[New_Position].Player.Color==WHITE))){
				//promotion
				int userinput=1;
        int promotion_number;
        int randomtype = rand() % 4;
        
        if (mode == 1){
          promotion_number = randomtype + 2;
          if (promotion_number>= 2 && promotion_number<=5){
				    	Pieces[New_Position].TYPE = promotion_number;
			    		char newnames[4] = "RNBQ";
			    		Pieces[New_Position].Name[1] = newnames[promotion_number-2];
		    			userinput = 0;}
        }
        else{
				while (userinput==1){
				printf("Pawn can be promoted: enter 2 for ROOK, 3 for KNIGHT, 4 for BISHOP, 5 for QUEEN\n");
				scanf("%d", &promotion_number);
				if (promotion_number>= 2 && promotion_number<=5){
					Pieces[New_Position].TYPE = promotion_number;
					char newnames[4] = "RNBQ";
					Pieces[New_Position].Name[1] = newnames[promotion_number-2];
					userinput = 0;}
				else{//printf("Invalid response. Please try again\n");
				}
				}}
	}}

int kingcheck(int Cur_Position, int New_Position, int color){
		int check = 0;
    int temp_replace_type;
   int temp_replace_color;
		int temp_holder_type;
   int Current_color_turn = color;
   if (Cur_Position >= 0 && New_Position >= 0){
    temp_replace_type = Pieces[New_Position].TYPE;
    temp_replace_color = Pieces[New_Position].Player.Color;
	  temp_holder_type = Pieces[Cur_Position].TYPE;
		Pieces[Cur_Position].TYPE= EMPTY;
		Pieces[New_Position].TYPE=temp_holder_type;
		
	 Current_color_turn = Pieces[Cur_Position].Player.Color;
		Pieces[Cur_Position].Player.Color = DNE;
		Pieces[New_Position].Player.Color = Current_color_turn;
   }
   
for (int i=0; i<64; i++){ // iterates over the 64 space board
	int enemy_cur_row = i / 8;
	int enemy_cur_col = i % 8;

	if (Pieces[i].Player.Color == !color){ // looking for enemy pieces
		if(Pieces[i].TYPE == PAWN){
		// left attack
			if (enemy_cur_col-1>=0){
      
				if (Pieces[i].Player.Color == WHITE && enemy_cur_row-1>=0){
					if (Pieces[i-9].Player.Color!=Pieces[i].Player.Color && Pieces[i-(9)].TYPE == KING){
							check += 1;
    //                        printf("pawn ");
              break;}}
			if (Pieces[i].Player.Color==BLACK && enemy_cur_row+1<=7){
					if (Pieces[i+7].Player.Color!=Pieces[i].Player.Color && Pieces[i+7].TYPE == KING){
							check += 1;
      //                      printf("pawn ");
              break;}}}
              
		// right attack
			if (enemy_cur_col+1<=7){
				if (Pieces[i].Player.Color == WHITE && enemy_cur_row-1>=0){
					if (Pieces[i-7].Player.Color!=Pieces[i].Player.Color && Pieces[i-(7)].TYPE == KING){
							check += 1;
        //                    printf("pawn ");
                            break;}}
			if (Pieces[i].Player.Color==BLACK && enemy_cur_row+1<=7){
					if (Pieces[i+9].Player.Color!=Pieces[i].Player.Color && Pieces[i+(9)].TYPE == KING){
							check += 1;
            //                printf("pawn ");
                            break;}}}
              }
              
			
		if(Pieces[i].TYPE == ROOK){
			for (int z = 1; z<8;z++){
			// up
				if (enemy_cur_row-z>=0){

     //        printf("compare %d %d for %d \n", Pieces[i].Player.Color, Pieces[i-(z*8)].Player.Color,i-(z*8) );
     //        printf(" is it empty %d %d\n", Pieces[i].TYPE, Pieces[i-(z*8)].TYPE);

						if (Pieces[i].Player.Color!=Pieces[i-(z*8)].Player.Color && Pieces[i-(z*8)].TYPE == KING){
							check += 1;
            //                printf(" %d rook ", i);
              break;}
						if (Pieces[i-(z*8)].TYPE != EMPTY){
							break;}}}
			// down
      for (int z = 1; z<8;z++){
				if (enemy_cur_row+z<=7){

     //        printf("compare %d %d for %d \n", Pieces[i].Player.Color, Pieces[i+(z*8)].Player.Color, i+(z*8));
     //        printf(" is it empty %d %d\n", Pieces[i].TYPE, Pieces[i+(z*8)].TYPE);

						if (Pieces[i].Player.Color!=Pieces[i+(z*8)].Player.Color && Pieces[i+(z*8)].TYPE == KING){
							check += 1;
           //                 printf(" %d rook ", i);
              break;}
						if (Pieces[i+(z*8)].TYPE != EMPTY){
							break;}}}
						
			// left
      for (int z = 1; z<8;z++){
				if (enemy_cur_col-z>=0){

    //         printf("compare %d %d for %d \n", Pieces[i].Player.Color, Pieces[i-z].Player.Color, i-(z));
    //         printf(" is it empty %d %d\n", Pieces[i].TYPE, Pieces[i-z].TYPE);

						if (Pieces[i].Player.Color!=Pieces[i-z].Player.Color && Pieces[i-(z)].TYPE == KING){
							check += 1;
     //                       printf(" %d rook ", i);
              break;}
						if (Pieces[i-(z)].TYPE != EMPTY){
							break;}}}
			// right
      for (int z = 1; z<8;z++){
				if (enemy_cur_col+z<=7){

  //           printf("compare %d %d for %d \n", Pieces[i].Player.Color, Pieces[i+z].Player.Color, i+(z));
  //           printf(" is it empty %d %d\n", Pieces[i].TYPE, Pieces[i+z].TYPE);

						if ((Pieces[i].Player.Color!=Pieces[i+z].Player.Color) && (Pieces[i+z].TYPE == KING)){
							check += 1;
  //                          printf(" %d rook ", i);
              break;}
						if (Pieces[i+z].TYPE != EMPTY){
							break;}}}
       if (check!=0){
         break;} // second break needed to get out of the forloop 0-63
              }
		
		if(Pieces[i].TYPE == BISHOP){
			for (int z = 1; z<8;z++){	
				if (enemy_cur_row-z>=0&& enemy_cur_col-z>=0){
					if ((Pieces[i-9*z].Player.Color != Pieces[i].Player.Color)&&(Pieces[i-9*z].TYPE == KING)){
							check += 1;
    //                        printf("%d bishop ",i);
              break;}
						if (Pieces[i-(z*9)].TYPE != EMPTY){
							break;}}}
      	for (int z = 1; z<8;z++){	
				if (enemy_cur_row-z>=0 && enemy_cur_col+z<=7){
					if ((Pieces[i-7*z].Player.Color != Pieces[i].Player.Color)&&(Pieces[i-7*z].TYPE == KING)){
							check += 1;
    //                        printf("%d bishop ",i);
              break;}
						if (Pieces[i-(z*7)].TYPE != EMPTY){
							break;}}}		
							
			//down
      	for (int z = 1; z<8;z++){	
			if (enemy_cur_row+z<=7 && enemy_cur_col-z>=0){
					if ((Pieces[i+7*z].Player.Color != Pieces[i].Player.Color)&& (Pieces[i+7*z].TYPE == KING)){
							check += 1;
       //                     printf("%d bishop ",i);
              break;}
						if (Pieces[i+(z*7)].TYPE != EMPTY){
							break;}}}
       	for (int z = 1; z<8;z++){	                                 
				if (enemy_cur_row+z<=7 && enemy_cur_col+z<=7){
					if ((Pieces[i+9*z].Player.Color != Pieces[i].Player.Color)&&(Pieces[i+9*z].TYPE == KING)){
							check += 1;
     //                       printf("%d bishop ",i);
              break;}
						if (Pieces[i+(z*9)].TYPE != EMPTY){
							break;}}}		
       if (check!=0){
         break;}// second break needed to get out of the forloop 0-63
                                     }
       
       
		
		if (Pieces[i].TYPE == KNIGHT){
			// 8 different possible moves
			if (enemy_cur_col-1 >=0 && enemy_cur_row-2 >= 0){
				if (Pieces[i-1-2*8].Player.Color != Pieces[i].Player.Color && Pieces[i-1-2*8].TYPE == KING){
					check += 1;
    //                printf("1knight ");
          break;}}
			
			if (enemy_cur_col-2 >=0 && enemy_cur_row-1 >= 0){
				if (Pieces[i-2-1*8].Player.Color != Pieces[i].Player.Color && Pieces[i-2-1*8].TYPE == KING){
					check += 1;
  //                  printf("2knight ");
          break;}}
			if (enemy_cur_col+1 <=7 && enemy_cur_row-2 >= 0){
				if (Pieces[i+1-2*8].Player.Color != Pieces[i].Player.Color && Pieces[i+1-2*8].TYPE == KING){
					check += 1;
   //                 printf("3knight ");
          break;}}
			if (enemy_cur_col-1 >=0 && enemy_cur_row+2 <= 7){
				if (Pieces[i-1+2*8].Player.Color != Pieces[i].Player.Color && Pieces[i-1+2*8].TYPE == KING){
					check += 1;
  //                  printf("4knight ");
          break;}}
			if (enemy_cur_col+2 <= 7 && enemy_cur_row-1 >= 0){
				if (Pieces[i+2-1*8].Player.Color != Pieces[i].Player.Color && Pieces[i+2-1*8].TYPE == KING){
					check += 1;
    //                printf("5knight ");
          break;}}
			if (enemy_cur_col-2 >= 0 && enemy_cur_row+1 <= 7){
			if (Pieces[i-2+1*8].Player.Color != Pieces[i].Player.Color && Pieces[i-2+1*8].TYPE == KING){
					check += 1;
   //                 printf("6knight ");
          break;}}
			if (enemy_cur_col+1 <=7 && enemy_cur_row+2 <= 7){
			if (Pieces[i+1+2*8].Player.Color != Pieces[i].Player.Color && Pieces[i+1+2*8].TYPE == KING){
					check += 1;
    //                printf("7knight ");
          break;}}
			if (enemy_cur_col+2 <=7 && enemy_cur_row+1 <= 7){
			if (Pieces[i+2+1*8].Player.Color != Pieces[i].Player.Color && Pieces[i+2+1*8].TYPE == KING){
					check += 1;
  //                  printf("8knight ");
          break;}}
          
			}
		
		if(Pieces[i].TYPE == QUEEN){
			// 8 different directions
			for (int z = 1; z<8;z++){
			// up
				if (enemy_cur_row-z>=0){
					if ((Pieces[i].Player.Color!=Pieces[i-(z*8)].Player.Color)&&(Pieces[i-(z*8)].TYPE == KING)){
							check += 1;
     //                       printf("%d queen ",i);
              break;}
						if (Pieces[i-(z*8)].TYPE != EMPTY){
							break;}}}
			// down
      for (int z = 1; z<8;z++){
				if (enemy_cur_row+z<=7){
					if ((Pieces[i].Player.Color!=Pieces[i+(z*8)].Player.Color)&& (Pieces[i+(z*8)].TYPE == KING)){
							check += 1;
     //                       printf("%d queen ",i);
              break;}
						if (Pieces[i+(z*8)].TYPE != EMPTY){
							break;}}}
						
			// left
      for (int z = 1; z<8;z++){
				if (enemy_cur_col-z>=0){
					if ((Pieces[i].Player.Color!=Pieces[i-z].Player.Color)&& (Pieces[i-(z)].TYPE == KING)){
							check += 1;
      //                      printf("%d queen ",i);
              break;}
						if (Pieces[i-(z)].TYPE != EMPTY){
							break;}}}
			// right
      for (int z = 1; z<8;z++){
				if (enemy_cur_col+z<=7){
					if ((Pieces[i].Player.Color!=Pieces[i+z].Player.Color)&&(Pieces[i+z].TYPE == KING)){
							check += 1;
       //                     printf("%d queen ",i);
              break;}
						if (Pieces[i+z].TYPE != EMPTY){
							break;}}}
					//upleft		
			for (int z = 1; z<8;z++){	
				if (enemy_cur_row-z>=0&& enemy_cur_col-z>=0){
					if ((Pieces[i-9*z].Player.Color != Pieces[i].Player.Color)&&(Pieces[i-9*z].TYPE == KING)){
							check += 1;
      //                      printf("%d queen ",i);
              break;}
						if (Pieces[i-(z*9)].TYPE != EMPTY){
							break;}}}
      //upright                                  
      	for (int z = 1; z<8;z++){	
				if (enemy_cur_row-z>=0 && enemy_cur_col+z<=7){
					if ((Pieces[i-7*z].Player.Color != Pieces[i].Player.Color)&&(Pieces[i-7*z].TYPE == KING)){
							check += 1;
      //                      printf("%d queen ",i);
              break;}
						if (Pieces[i-(z*7)].TYPE != EMPTY){
							break;}}}		
							
			//downleft
      	for (int z = 1; z<8;z++){	
			if (enemy_cur_row+z<=7 && enemy_cur_col-z>=0){
					if ((Pieces[i+7*z].Player.Color != Pieces[i].Player.Color)&&(Pieces[i+7*z].TYPE == KING)){
							check += 1;
      //                      printf("%d queen ",i);
              break;}
						if (Pieces[i+(z*7)].TYPE != EMPTY){
							break;}}}
          //downright                              
       	for (int z = 1; z<8;z++){	                                 
				if (enemy_cur_row+z<=7 && enemy_cur_col+z<=7){
					if ((Pieces[i+9*z].Player.Color != Pieces[i].Player.Color)&& (Pieces[i+9*z].TYPE == KING)){
							check += 1;
      //                      printf("%d queen ",i);
              break;}
						if (Pieces[i+(z*9)].TYPE != EMPTY){
							break;}}}		
       if (check!=0){
         break;}}// second break needed to get out of the forloop 0-63
			
		if(Pieces[i].TYPE == KING){
			// up
			if (enemy_cur_row-1>=0){
				if ((Pieces[i-8].Player.Color != Pieces[i].Player.Color)&&(Pieces[i-8].TYPE == KING)){
							check += 1;
      //                      printf("%d king ", i);
              break;} 
							
				if (enemy_cur_col-1>=0){
					if ((Pieces[i-9].Player.Color != Pieces[i].Player.Color)&& (Pieces[i-9].TYPE == KING)){
							check += 1;
       //                     printf("king ");
              break;}} 
				if (enemy_cur_col+1<=7){
					if ((Pieces[i-7].Player.Color != Pieces[i].Player.Color)&& (Pieces[i-7].TYPE == KING)){
							check += 1;
      //                      printf("king ");
              break;}}}
							
			if (enemy_cur_row+1<=7){
					if ((Pieces[i].Player.Color!=Pieces[i+8].Player.Color)&&(Pieces[i+8].TYPE == KING)){
							check += 1;
      //                      printf("king ");
              break;} 
							
				if (enemy_cur_col-1>=0){
					if ((Pieces[i+7].Player.Color != Pieces[i].Player.Color)&& (Pieces[i+7].TYPE == KING)){
							check += 1;
    //                        printf("king ");
              break;}} 
				if (enemy_cur_col+1<=7){
					if ((Pieces[i+9].Player.Color != Pieces[i].Player.Color)&&(Pieces[i+9].TYPE == KING)){
							check += 1;
    //                        printf("king ");
              break;}}}	
			// left	
			if (enemy_cur_col-1>=0){
					if ((Pieces[i].Player.Color!=Pieces[i-1].Player.Color)&& (Pieces[i-(1)].TYPE == KING)){
							check += 1;
    //                        printf("king ");
              break;}}		
			// right
				if (enemy_cur_col+1>=0){
					if ((Pieces[i].Player.Color!=Pieces[i+1].Player.Color)&&(Pieces[i+1].TYPE == KING)){
							check += 1;
      //                      printf("king ");
              break;}}	
              }// end of king if statements
              }// end of if statements for color matching
              }// end of for loop
							
// switch back
 if (Cur_Position >= 0 && New_Position >= 0){
 //printf("how");
		Pieces[New_Position].TYPE= temp_replace_type;
		Pieces[Cur_Position].TYPE=temp_holder_type;
		
		Pieces[New_Position].Player.Color = temp_replace_color;
		Pieces[Cur_Position].Player.Color = Current_color_turn;
   }
   // return true or false of the check function
		if (check != 0){
		return 1;}
		return 0;
		}
			
int CheckMove(int Cur_Position, int New_Position, int version) {
  // returns 0 if illegal, returns 1 if legal

  int i, j, k;

  if (((63 >= Cur_Position) && (Cur_Position >= 0)) && ((63 >= New_Position) && (New_Position >= 0))) {

  // turn based condition
  // if currentplayercolor == Pieces[Cur_Position].Player.Color){
  // continue (place -} enclosing all of the piece checkers)

    if (kingcheck(Cur_Position,New_Position, Pieces[Cur_Position].Player.Color) == 1){ // check to see the move would leave king exposed, so it exits at check independent of whether the piece type move is legal or not
  //      printf(" %d  ", New_Position);
     //   printf("Error king check  \n");
        return 0;}
//-------------------------------ROOK--------------------------------------
   if (Pieces[Cur_Position].TYPE == ROOK ){

			int direction = 0;
			int t = 0;												//		0
			int cur_row = Cur_Position / 8;							//		0
			int cur_col = Cur_Position % 8;							//	1 1 R 3 3
			int new_row = New_Position / 8;							//		2
			int new_col = New_Position % 8;							//		2
    		if (Pieces[New_Position].Player.Color != Pieces[Cur_Position].Player.Color){
			if (cur_col == new_col){
				if (new_row > cur_row){
					direction += 2;
				}
			}
			else if (cur_row == new_row){
				direction += 1;
				if (new_col > cur_col){
					direction += 2;
				}
			}
			else{ return 0;}

			if (direction == 1){
				for (t = cur_col ; t>=0 ; t-=1){
					if (new_col == t){Pieces[Cur_Position].FirstMove = NA;return 1;}
					if (Pieces[cur_row*8 -1 + t].TYPE != EMPTY){
						if (Pieces[cur_row*8 -1+ t].Player.Color != Pieces[Cur_Position].Player.Color){
							if (new_col == t-1){Pieces[Cur_Position].FirstMove = NA;return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}
			if (direction == 3){
				for (t = cur_col ; t<=7 ; t+=1){
					if (new_col == t){Pieces[Cur_Position].FirstMove = NA;return 1;}
					if (Pieces[cur_row*8 + 1 + t].TYPE != EMPTY) {
						if (Pieces[cur_row*8 + 1 + t].Player.Color != Pieces[Cur_Position].Player.Color){
							if (new_col == t+1){Pieces[Cur_Position].FirstMove = NA;return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}
			if (direction == 0){
				for (t = cur_row ; t>=1 ; t-=1){
					if (new_row == t){Pieces[Cur_Position].FirstMove = NA;return 1;}
					if (Pieces[t*8 - 8 + cur_col].TYPE != EMPTY){
						if (Pieces[t*8 - 8 + cur_col].Player.Color != Pieces[Cur_Position].Player.Color){
							if (new_row == t-1){Pieces[Cur_Position].FirstMove = NA;return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}
			if (direction == 2){
				for (t = cur_row ; t<=7 ; t+=1){
					if (new_row == t){Pieces[Cur_Position].FirstMove = NA;return 1;}
					if (Pieces[t*8 + 8 + cur_col].TYPE != EMPTY){
						if (Pieces[t*8 +8+ cur_col].Player.Color != Pieces[Cur_Position].Player.Color){
							if (new_row == t+1){Pieces[Cur_Position].FirstMove = NA;return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}
      }
	}
//------------------------------KING-----------------------------------------

   if (Pieces[Cur_Position].TYPE == KING ){

		int cur_row = Cur_Position / 8;
		int cur_col = Cur_Position % 8;
		int new_row = New_Position / 8;
		int new_col = New_Position % 8;

		if (Pieces[New_Position].Player.Color != Pieces[Cur_Position].Player.Color){

			if ((abs(new_col-cur_col)==1 && abs(new_row-cur_row)==1)||(abs(new_col-cur_col)==1 && abs(new_row-cur_row)==0)
			||(abs(new_col-cur_col)==0 && abs(new_row-cur_row)==1)){
					Pieces[Cur_Position].FirstMove = NA;
//					printf("king ");
					return 1;
				}
			// castling
			if (Pieces[Cur_Position].FirstMove == NOFIRSTMOVE){
				// right castling
				if ((New_Position-Cur_Position)==2 && Pieces[New_Position+1].TYPE == ROOK && Pieces[New_Position+1].FirstMove == NOFIRSTMOVE){
					int check = 0;
					for (i = 1; i<3; i=i+1){
						if (Pieces[Cur_Position+i].TYPE != EMPTY){
							check += 1;}
               if (kingcheck(Cur_Position, Cur_Position+i,Pieces[Cur_Position].Player.Color)==1){
                   return 0;}
								}
					if (check == 0){ 
						if (version == 1){
							Pieces[Cur_Position].FirstMove = FIRST;
							Pieces[New_Position+1].FirstMove = FIRST;}
						printf("right castle \n");
						return 1;}
						}
				// left castling
				if ((New_Position-Cur_Position-cur_col)==-2 && Pieces[New_Position-2].TYPE== ROOK && Pieces[New_Position-2].FirstMove == NOFIRSTMOVE){
					int check = 0;
					for (i = 1; i<=3; i=i+1){ 
						if (Pieces[Cur_Position-i].TYPE != EMPTY){
							check += 1;}
							if (kingcheck(Cur_Position, Cur_Position-i,Pieces[Cur_Position].Player.Color)==1){
                   return 0;}}
					if (check == 0){
						if (version == 1){
						Pieces[Cur_Position].FirstMove = FIRST;
						Pieces[New_Position-2].FirstMove = FIRST;}
						printf("left castle \n");
						return 1;}}}}
			return 0;}




//-------------------------------KNIGHT--------------------------------------
		if (Pieces[Cur_Position].TYPE == KNIGHT) {
			int cur_row = Cur_Position / 8;
			int cur_col = Cur_Position % 8;
			int new_row = New_Position / 8;
			int new_col = New_Position % 8;
			if (Pieces[New_Position].Player.Color != Pieces[Cur_Position].Player.Color) {
			    if ((abs(new_col - cur_col) == 2 && abs(new_row - cur_row) == 1) || (abs(new_col - cur_col) == 1 && abs(new_row - cur_row) == 2)) {
//			    	printf("knight ");
					return 1;}
				else {
					return 0;}}
			else{
      return 0;}}

//---------------------PAWN--------------------------------------
if (Pieces[Cur_Position].TYPE == PAWN ){

			int cur_row = Cur_Position / 8;
			int cur_col = Cur_Position % 8;
			int new_row = New_Position / 8;
			int new_col = New_Position % 8;

			if (Pieces[New_Position].Player.Color != Pieces[Cur_Position].Player.Color){ // as long as colors dont match

				if (Pieces[Cur_Position].FirstMove == NOFIRSTMOVE){
					//checks special first move (condition statement combines both black and white conditions)
					if ((((new_col-cur_col)==0) && ((new_row-cur_row)==2) && cur_row == 1 && (Pieces[Cur_Position].Player.Color == BLACK))||
					(((new_col-cur_col)==0) && ((new_row-cur_row)==-2) && cur_row == 6 && (Pieces[Cur_Position].Player.Color == WHITE))){
						// check if moving through empty spaces
						int legalpassing = 0;
						int  i;
						for (i = 1; i<3; i=i+1){
							if ((Pieces[Cur_Position+(i*8)].TYPE == EMPTY && Pieces[Cur_Position].Player.Color == BLACK)||
								(Pieces[Cur_Position-(i*8)].TYPE == EMPTY && Pieces[Cur_Position].Player.Color == WHITE)){
								legalpassing += 1;
							}
						}
						if (legalpassing == 2){
							if (version == 1){
							Pieces[Cur_Position].FirstMove = FIRST;}
		//					printf("pawn first ");
							return 1;
						}}}
				// normal move
				if ((((new_col-cur_col)==0) && ((new_row-cur_row)==1) && (Pieces[Cur_Position].Player.Color == BLACK))||
				(((new_col-cur_col)==0)&&((new_row-cur_row)==-1)&&(Pieces[Cur_Position].Player.Color == WHITE))){
					if (Pieces[New_Position].TYPE == EMPTY){
						if (version == 1){
						Pieces[Cur_Position].FirstMove = NA;}
		//				printf("pawn");
						return 1;}}
				// attack diagonal
				if ((abs(new_col-cur_col)==1) && (((new_row-cur_row)==1 && Pieces[Cur_Position].Player.Color == BLACK)||
				((new_row-cur_row)==-1 && Pieces[Cur_Position].Player.Color == WHITE))){
					if (Pieces[New_Position].TYPE != EMPTY){ // normal attack
					if (version == 1){
						Pieces[Cur_Position].FirstMove = NA;}
	//					printf("pawn attack");
						return 1;}

					// ENPASSANTE - under attack if statement
					if ((Pieces[New_Position].TYPE == EMPTY)){
						if(Pieces[Cur_Position].Player.Color == BLACK){
							if (Pieces[New_Position-8].TYPE == PAWN && (Pieces[New_Position-8].Player.Color != Pieces[Cur_Position].Player.Color) && Pieces[New_Position-8].FirstMove == FIRST){
                 // remove enemy pawn
				 				if (version == 1){
								Pieces[Cur_Position].FirstMove = NA;}
				//				printf("enpassente black \n");
								return 1;}
								}
						else if (Pieces[Cur_Position].Player.Color == WHITE){
							if(Pieces[New_Position+8].TYPE == PAWN && (Pieces[New_Position+8].Player.Color != Pieces[Cur_Position].Player.Color) && Pieces[New_Position+8].FirstMove == FIRST){
                 // need dto add remove enemy pawn
				 				if (version == 1){
								Pieces[Cur_Position].FirstMove = NA;}
			//					printf("enpassente white \n");
								return 1;}
								}
							}
					}
				return 0; // illegal move
				}
				else{
				return 0;}}

//--------------------------QUEEN-----------------------------------------
if(Pieces[Cur_Position].TYPE == QUEEN){
			int d;
			int direction2=0;
 			int r;													//		0
  			int cur_row = Cur_Position / 8;							//		0
  			int cur_col = Cur_Position % 8;							//	1 1 R 3 3
  			int new_row = New_Position / 8;							//		2
  			int new_col = New_Position % 8;							//		2
  			int direction = 0;										//  1 |   | 0
                      												//    	B
                      												//  2 |   | 3
     if (Pieces[New_Position].Player.Color != Pieces[Cur_Position].Player.Color){// protective layer to prevent cannibalism
  																	//check if it's moving forward or backward
  			if (Cur_Position >= New_Position) {
    			i = Cur_Position;
    			j = New_Position;
  			}
  			else{
    			i = New_Position;
    			j = Cur_Position;
    			direction += 2;
  			}
  			k = i - j;

  			// check we should use either rookmoves or bishopmoves, 1 for bishop and 2 for rook
 			if (k%7 == 0){d = 1;}
  			else if(k%9 == 0){d = 1;direction += 1;}

			else{

				if (cur_col == new_col){
					d = 2;
					if (new_row > cur_row){
					direction2 += 2;
					}
				}
			else if (cur_row == new_row){
				d = 2;
				direction2 += 1;
				if (new_col > cur_col){
					d = 2;
					direction2 += 2;
				}
			}
			else{ return 0;}


			}


			if (d ==1 ){																// if we are using bishop moves
 		 	int t;																								// check if the path was occupied by another piece

	

  			if (direction == 1){
				for (t = Cur_Position-9; t>=0 ; t-=9){															//  loop to check if the path is occupied by other pieces
					if ((Pieces[t].Player.Color == Pieces[Cur_Position].Player.Color)){return 0;}
					if (New_Position == t){return 1;}
					if ((Pieces[t].TYPE != EMPTY)){																//  if there is a piece on the path
						if (Pieces[t].Player.Color != Pieces[Cur_Position].Player.Color){						//  check if the piece are same color
							if (New_Position == t){return 1;}					 								//  if we have different color, then check if the move is a "capture"
							else{return 0;}
						}
						return 0;
					}
				}
			}
			if (direction == 0){
				for (t = Cur_Position-7; t>=0 ; t-=7){
					if ((Pieces[t].Player.Color == Pieces[Cur_Position].Player.Color)){return 0;}
					if (New_Position == t){return 1;}
					if (Pieces[t].TYPE != EMPTY){
						if (Pieces[t].Player.Color != Pieces[Cur_Position].Player.Color){
							if (New_Position == t){return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}
			if (direction == 2){
				for (t = Cur_Position+7; t<=64 ; t+=7){
					if ((Pieces[t].Player.Color == Pieces[Cur_Position].Player.Color)){return 0;}
					if (New_Position == t){return 1;}
					if (Pieces[t].TYPE != EMPTY){
						if (Pieces[t].Player.Color != Pieces[Cur_Position].Player.Color){
							if (New_Position == t){return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}
			if (direction == 3){
				for (t = Cur_Position+9; t<=64 ; t+=9){
					if ((Pieces[t].Player.Color == Pieces[Cur_Position].Player.Color)){return 0;}
					if (New_Position == t){return 1;}
					if (Pieces[t].TYPE != EMPTY) {
				//		printf("meet\n");
						//return 0;
						if (Pieces[t].Player.Color != Pieces[Cur_Position].Player.Color){
							if (New_Position == t){return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}
}			// biship part done
  // check rook movements

  // test if its on ther path

  // test if there is other pieces occupy the path
  if (d ==2 ){



  if (direction2 == 1){
    for (r = cur_col ; r>=0 ; r-=1){
      if (new_col == r){return 1;}
      if (Pieces[cur_row*8-1 + r].TYPE != EMPTY){
        if (Pieces[cur_row*8 -1 + r].Player.Color != Pieces[Cur_Position].Player.Color){
          if (new_col == r-1){return 1;}
          else{return 0;}
        }
        return 0;
      }
    }
  }

  if (direction2 == 3){
    for (r = cur_col ; r<=7 ; r+=1){
      if (new_col == r){return 1;}
      if (Pieces[cur_row*8 +1+ r].TYPE != EMPTY){
        if (Pieces[cur_row*8 + 1 + r].Player.Color != Pieces[Cur_Position].Player.Color){
          if (new_col == r+1){
               Pieces[Cur_Position].FirstMove = NA;
          return 1;}
          else{return 0;}
        }
        return 0;
      }
    }
  }


  if (direction2 == 0){
    for (r = cur_row ; r>=1 ; r-=1){
      if (new_row == r){return 1;}
      if (Pieces[r*8 - 8 + cur_col].TYPE != EMPTY){
        if (Pieces[r*8 - 8 + cur_col].Player.Color != Pieces[Cur_Position].Player.Color){
          if (new_row == r-1){
           Pieces[Cur_Position].FirstMove = NA;
          return 1;}
          else{return 0;}
        }
        return 0;
      }
    }
  }

  if (direction2 == 2){
    for (r = cur_row ; r<=7 ; r+=1){
      if (new_row == r){
         Pieces[Cur_Position].FirstMove = NA;
      return 1;}
      if (Pieces[r*8 + 8 + cur_col].TYPE != EMPTY){
        				if (Pieces[r*8 +8+ cur_col].Player.Color != Pieces[Cur_Position].Player.Color){
          			if (new_row == r+1){
             			Pieces[Cur_Position].FirstMove = NA;
          				return 1;}
         		 		else{return 0;}
        				}
        				return 0;
      				}
    			}
  			}
		}}
	}

//--------------------------BISHOP----------------------------------------
if (Pieces[Cur_Position].TYPE == BISHOP ){
			int direction = 0;						//  1 |   | 0
													//    	B
													//  2 |   | 3
			//check if it's moving forward or backward
			if (Cur_Position >= New_Position) {
				i = Cur_Position;
				j = New_Position;
			}
			else{
				i = New_Position;
				j = Cur_Position;
				direction += 2;
			}
			k = i - j;
			if (k == 0){return 0;}
			if (k%7 == 0){}																						//check if it's moving left or moving right
			else if(k%9 == 0){direction += 1;}
			else{return 0;}
			//printf("1111\n");

			if ((direction == 0) || (direction == 3)){															//	check if the piece meet the left/right boundary
				if(New_Position%8 <= Cur_Position%8){return 0;}
			}
			else{
				if(New_Position%8 >= Cur_Position%8){return 0;}
			}

			int t;																								// check if the path was occupied by another piece
	//		printf("%d\n",direction);

			if (direction == 1){
				for (t = Cur_Position-9; t>=0 ; t-=9){															//  loop to check if the path is occupied by other pieces
					if ((Pieces[t].Player.Color == Pieces[Cur_Position].Player.Color)){return 0;}
					if (New_Position == t){return 1;}
					if ((Pieces[t].TYPE != EMPTY)){																//  if there is a piece on the path
						if (Pieces[t].Player.Color != Pieces[Cur_Position].Player.Color){						//  check if the piece are same color
							if (New_Position == t){return 1;}					 								//  if we have different color, then check if the move is a "capture"
							else{return 0;}
						}
						return 0;
					}
				}
			}
			if (direction == 0){
				for (t = Cur_Position-7; t>=0 ; t-=7){
					if ((Pieces[t].Player.Color == Pieces[Cur_Position].Player.Color)){return 0;}
					if (New_Position == t){return 1;}
					if (Pieces[t].TYPE != EMPTY){
						if (Pieces[t].Player.Color != Pieces[Cur_Position].Player.Color){
							if (New_Position == t){return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}
			if (direction == 2){
				//printf("\nk\n");
				for (t = Cur_Position+7; t<=64 ; t+=7){
					//printf("1\n");
					if ((Pieces[t].Player.Color == Pieces[Cur_Position].Player.Color)){return 0;}
					if (New_Position == t){return 1;}
					if (Pieces[t].TYPE != EMPTY){
						//printf("a\n\n");
						if (Pieces[t].Player.Color != Pieces[Cur_Position].Player.Color){
							//printf("b\n\n");
							if (New_Position == t){return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}
			if (direction == 3){
				for (t = Cur_Position+9; t<=64 ; t+=9){
					if ((Pieces[t].Player.Color == Pieces[Cur_Position].Player.Color)){return 0;}
					if (New_Position == t){return 1;}
					if (Pieces[t].TYPE != EMPTY) {
				
						//return 0;
						if (Pieces[t].Player.Color != Pieces[Cur_Position].Player.Color){
							if (New_Position == t){return 1;}
							else{return 0;}
						}
						return 0;
					}
				}
			}

 //   printf("Bishop");
	return 1;
  }
  else {
    return 0;
  }}
  return 0;
}



