
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "AI.h"
#include "logfile.h"
#include "gamestateflow.h"
int ai,opponent;
int x = 8;
int y = 16;
int aiPieceNames[7] = {EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
int sentcurposition,sentnewposition;
int first_move_holder;

//helper functions
/*int sendCurPos(){
  return sentcurposition;
}

int sendNewPos(){
return sentnewposition;
}*/

Chess_moveList *CreateMoveList(void)
{
  Chess_moveList *movelist;
  movelist = malloc(sizeof(Chess_moveList));
  if (! movelist)
    {
      printf("Failed to create memory");
      exit(10);
    }

    movelist->Length = 0;
    movelist->First = NULL;
    movelist->Last = NULL;
    return movelist;
}
//MIGHT NOT WORK!!
void DeleteMoveList(Chess_moveList *List){
	/* to be implemented */
  Chess_move *e, *n;
  Chess_position *i;
  assert(List);
  e = List->First;
  while(e)
    {
      n = e->Next;
      free(e);
      e = n;
    }
  free(List);
}

/*static Chess_move DeleteMove(Chess_move *Chess_Move){
  assert(Chess_Move);
  assert(Chess_Move->Piece);
  assert(Chess_Move->Cur_position);
  assert(Chess_Move->New_position);

  free(Chess_Move->Piece);
  free(Chess_Move->Cur_position);
  free(Chess_Move->New_position);

  Chess_Move->Piece = NULL;
  Chess_Move->Cur_position = NULL;
  Chess_Move->New_position = NULL;
  free(Chess_Move);

}
REFER TO DELETE IMAGE IN IMAGE.C*/

/*static Chess_position DeleteMove(Chess_move *Chess_Move){
  Chess_position *i;
  assert(Chess_Move);
  i = Chess_Move->Cur_position;
  free(i);
  i = Chess_Move->New_position;
  free(i);
  return i;
}*/

static Chess_move *NewMoveEntry(unsigned int Cur_Position, unsigned int New_Position){
  Chess_move *e;
  e = malloc(sizeof(Chess_move));
  if (! e)
  {
    perror("Out of memory! Aborting...");
    exit(10);
  } /* fi */
  e->List = NULL;
  e->Next = NULL;
  e->Prev = NULL;
  e->Cur_position = Cur_Position;
  e->New_position = New_Position;
  return e;
}

void AppendMove(Chess_moveList *List, unsigned int Cur_Position, unsigned int New_Position){
  Chess_move *e = NULL;
  assert(List);
  //assert(Cur_Position);
  //assert(New_Position);
  //printf("it works at appendmove\n" );
  e = NewMoveEntry(Cur_Position, New_Position);
  //printf(" It works at NewMoveEntry \n" );
  if (List->Last)
  {
    e->List = List;
    e->Next = NULL;
    e->Prev = List->Last;
    List->Last->Next = e;
    List->Last = e;
    e->Cur_position = Cur_Position;
    e->New_position = New_Position;
    e->points = NULL;
    //printf("\nnew position is %d\n", e->New_position);
  }
  else
  {
    e->List = List;
    e->Next = NULL;
    e->Prev = NULL;
    e->points = NULL;
    List->First = e;
    List->Last = e;

  }
  List->Length++;
}


void AIMove(){
 int i,j;
  //arbitrarily assigns 0 to the new location of the current pieces
  j = 0;
  Get_board();
  srand(time(NULL));
  Chess_moveList *AIMoves = CreateMoveList();
  Chess_moveList *CurrentPieces = CreateMoveList();
 
  //loop that checks for the current locations of all the opponent pieces on the board
  for (i=0; i<64; i++) {
    if (Pieces[i].Player.Color == MainMenuState3()){
      AppendMove(CurrentPieces,i,j);
      }
  }

  for (i=0; i<64; i++) {
    //inner loop
         first_move_holder = Pieces[i].FirstMove; // temp storage
    for (j=0; j<64; j++){
      //makes legal moves for each piece
      CheckMove(i,j,0);
          Pieces[i].FirstMove = first_move_holder; // restores
      if (CheckMove(i,j,0) == 1){
         if (Pieces[i].Player.Color == (3 + MainMenuState3()) % 2){
           if (i != j){
            AppendMove(AIMoves,i,j);
              }
            }
         }
      }
    }

    Chess_move *oppPiece = CurrentPieces->First;
    Chess_move *curpos = AIMoves->First;
    //Test code that checks if all the positions of the pieces are recovered
    /*while(oppPiece){
      printf("Current Postition of the white pieces are (%d,%d)\n",oppPiece->Cur_position,oppPiece->New_position);
      oppPiece = oppPiece->Next;
    }*/
    //loop that assigns points to each move
    int totalmoves = 0;
    while(curpos){
      curpos->points = 0;
      //printf("Current Postition, Final position, and points are (%d,%d,%d)\n",curpos->Cur_position,curpos->New_position,curpos->points);
      //if current position of white = new position of black - award points
      /*if (curpos->New_position == oppPiece->Cur_position){
        if (Pieces[oppPiece->Cur_position].TYPE == 1){
          curpos->points = 1;
        }
        else if (Pieces[oppPiece->Cur_position].TYPE == 2){
          curpos->points = 5;
        }
        else if (Pieces[oppPiece->Cur_position].TYPE == 3){
          curpos->points = 3;
        }
        else if (Pieces[oppPiece->Cur_position].TYPE == 4){
          curpos->points = 3;
        }
        else if (Pieces[oppPiece->Cur_position].TYPE == 5){
          curpos->points = 9;
        }
      }*/
      curpos = curpos->Next;
      totalmoves++;
      //printf("oppPiece not null");
      //oppPiece = oppPiece->Next;
    }

    //printf("broke before curpos assignment \n");

    curpos = AIMoves->First;
    //printf("broke after curpos assignment \n");
    Chess_move *temp = AIMoves->First;
    int similarmoves = 0;
    //printf("seg fault before here");
    while(curpos){
      if (curpos->points > temp->points){
        temp = curpos;
        similarmoves++;
        }
        curpos = curpos->Next;
        //printf("doing stuff\n");
    }

    //more test statements
    //printf("similarmoves = %d", similarmoves);
    if (similarmoves == 0){
      //"randomizer"
      int randomMove = rand() % totalmoves;
      temp = AIMoves->First;
      int n;
      for(n=0; n<=randomMove; n++){
        temp = temp->Next;
      }
    }

 //   printf("AI move list generated\n");
    //printf("Grand total of %d possible moves!\n",AIMoves->Length);
  //  printf("The best possible move is (%d,%d,%d)\n",temp->Cur_position,temp->New_position,temp->points);

     sentcurposition = temp->Cur_position;
     sentnewposition = temp->New_position;
     logfile(sentcurposition,sentnewposition);
    printf("Testing current and new position: (%d,%d)\n",sentcurposition ,sentnewposition);
    CheckMove(sentcurposition, sentnewposition,1);
    Move_Piece(sentcurposition, sentnewposition);
    
       Castling(sentnewposition);
    enpassant_risk_pawn_location = ENPASSANT(enpassant_risk_pawn_location, sentnewposition);
    Promotion(sentnewposition,1);  

    
    

    //deletes lists
    DeleteMoveList(AIMoves);
    DeleteMoveList(CurrentPieces);

  }

//--------------------------------------------------------------JUNGKOOK MODE-------------------------------------------------------------------------------------------------------
void JungKook(){
  int i,j;
  //arbitrarily assigns 0 to the new location of the current pieces
  j = 0;
  char *jungkookquotes[6]={"I gotta make it burn baby!🎶","Love is nothing stronger.♡₊˚ ༘ ◌¨̮͚ Than a boy with, than a boy with luv🎶",
                          "I'ma light it up like dynamite, whoa oh oh🎶", "Dy-na-na-na, na-na, na-na-na, na-na-na, life is dynamite🎶",
                          "Now thats smooth like butter!", "Great Move! Its in your DNA!🎶"
                        };
  char *boxes[64] =  {"a8","b8","c8","d8","e8","f8","g8","h8",
                      "a7","b7","c7","d7","e7","f7","g7","h7",
                      "a6","b6","c6","d6","e6","f6","g6","h6",
                      "a5","b5","c5","d5","e5","f5","g5","h5",
                      "a4","b4","c4","d4","e4","f4","g4","h4",
                      "a3","b3","c3","d3","e3","f3","g3","h3",
                      "a2","b2","c2","d2","e2","f2","g2","h2",
                      "a1","b1","c1","d1","e1","f1","g1","h1",};
  Get_board();
  
  srand(time(NULL));
  Chess_moveList *AIMoves = CreateMoveList();
  Chess_moveList *CurrentPieces = CreateMoveList();

  //loop that checks for the current locations of all the opponent pieces on the board
  for (i=0; i<64; i++) {
    if (Pieces[i].Player.Color == (3 + MainMenuState3()) % 2){
      AppendMove(CurrentPieces,i,j);
      }
  }

  for (i=0; i<64; i++) {
    //inner loop
     first_move_holder = Pieces[i].FirstMove; // temp storage for firstmove
    for (j=0; j<64; j++){
      //makes legal moves for each piece
      CheckMove(i,j,0);
      Pieces[i].FirstMove = first_move_holder;
      
      if (CheckMove(i,j,0) == 1){
         if (Pieces[i].Player.Color == MainMenuState3()){
           if (i != j){
            AppendMove(AIMoves,i,j);
              }
            }
         }
      }
    }

    Chess_move *oppPiece = CurrentPieces->First;
    Chess_move *curpos = AIMoves->First;
    //Test code that checks if all the positions of the pieces are recovered
    /*while(oppPiece){
      printf("Current Postition of the white pieces are (%d,%d)\n",oppPiece->Cur_position,oppPiece->New_position);
      oppPiece = oppPiece->Next;
    }*/
    //loop that assigns points to each move
    int totalmoves = 0;
    while(curpos){
      curpos->points = 0;
      //printf("Current Postition, Final position, and points are (%d,%d,%d)\n",curpos->Cur_position,curpos->New_position,curpos->points);
      //if current position of white = new position of black - award points
      /*if (curpos->New_position == oppPiece->Cur_position){
        if (Pieces[oppPiece->Cur_position].TYPE == 1){
          curpos->points = 1;
        }
        else if (Pieces[oppPiece->Cur_position].TYPE == 2){
          curpos->points = 5;
        }
        else if (Pieces[oppPiece->Cur_position].TYPE == 3){
          curpos->points = 3;
        }
        else if (Pieces[oppPiece->Cur_position].TYPE == 4){
          curpos->points = 3;
        }
        else if (Pieces[oppPiece->Cur_position].TYPE == 5){
          curpos->points = 9;
        }
      }*/
      curpos = curpos->Next;
      totalmoves++;
      //printf("oppPiece not null");
      //oppPiece = oppPiece->Next;
    }

    //printf("broke before curpos assignment \n");

    curpos = AIMoves->First;
    //printf("broke after curpos assignment \n");
    Chess_move *temp = AIMoves->First;
    int similarmoves = 0;
    //printf("seg fault before here");
    while(curpos){
      if (curpos->points > temp->points){
        temp = curpos;
        similarmoves++;
        }
        curpos = curpos->Next;
        //printf("doing stuff\n");
    }



    //more test statements
    //printf("similarmoves = %d", similarmoves);
    if (similarmoves == 0){
      //"randomizer"
      int randomMove = rand() % totalmoves;
      temp = AIMoves->First;
      int n;
      for(n=0; n<=randomMove; n++){
        temp = temp->Next;
      }
    }


    //printf("AI move list generated\n");
    //printf("Grand total of %d possible moves!\n",AIMoves->Length);
    //printf("The best possible move is (%d,%d,%d)\n",temp->Cur_position,temp->New_position,temp->points);
     sentcurposition = temp->Cur_position;
     sentnewposition = temp->New_position;


     //logfile(sentcurposition,sentnewposition);
     printf("Jungkook [BTS]: Move %s to %s. %s\n", boxes[sentcurposition],boxes[sentnewposition],jungkookquotes[rand()%6]);
     
    //printf("Testing current and new position: (%d,%d)\n",sentcurposition ,sentnewposition);

    //deletes lists
    DeleteMoveList(AIMoves);
    DeleteMoveList(CurrentPieces);



  }

  int checkmate(int check, int color){
    int i,j,length,  first_move_holder;
  Chess_moveList *Moves = CreateMoveList();
  //loop that checks for the legal moves of all the pieces on the board of the black color
  //if you want to change it to append white moves , change Player.Color to == 0
  for (i=0; i<64; i++) {
    //inner loop
     first_move_holder = Pieces[i].FirstMove; 
    for (j=0; j<64; j++){
      //makes legal moves for each piece
      CheckMove(i,j,0);
      Pieces[i].FirstMove = first_move_holder; 
      if (CheckMove(i,j,0) == 1){
         if (Pieces[i].Player.Color == color){
           if (i != j){
            AppendMove(Moves,i,j);
              }
            }
         }
      }
    }
    length = Moves->Length;
   DeleteMoveList(Moves);
 //  printf("length %d", length);
   
  	if (check==0 && length ==0){
  		printf("Stalemate\nNo more legal moves can be made\n");
  		return 1;}
  	if (check==1 && length ==0){
  		printf("Checkmate\n");
  		return 1;}
  	return 0;}
