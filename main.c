#include "chess_move.h"
//testing gamestateflow file
#include "gamestateflow.h"
#include "AI.h"
#include "logfile.h"

/*changes - revamped so that instead of typing a number to select which piece to move
and a number for a location, you can type in the coordinate to move it there */

int main(){

	//to tell us exact type of piece for debugging
	const char* pieceNames[7] = {"EMPTY", "PAWN", "ROOK", "KNIGHT","BISHOP","QUEEN","KING"};
	const char* Colors[3] = {"BLACK", "WHITE", "DNE"};
	int i,j,k, gamestate = 1;
	int CurPosition, NewPosition;
	//added by abhishek - for translating location to coordinate plane
	char NewPositionText[60];
	char CurPositionText[60];
  int count1,count2;
  int firstChar;
  int secondChar;
  int playercolor;
  int jungkookie;
  char letters[9] = "abcdefgh";
  char numbers[9] = "12345678";
  char initial_message[100] = "\nJungkook [BTS] - \"AYO LADIES AND GENTLEMENN--\n";
  char end_message[220] = "\nThank you for checking out JUNGKOOK CHESS. We have to let you go now ... \n Jungkook [BTS] - \"But you're my everything ... I NEED U GIRLL WAE\"";
  char winning_message[220] = "\nJungkook [BTS] - \"Another trophy, my hands carry 'em \n Too many that I can't even count 'em (Turn it up now) \n Mic drop, \t mic drop\"\n";


  // turn based by color:
  Chess_player_color Player_Turn_Color = WHITE;
  int userinputStage = 1;

  // debugging CHANG MODE
  int AIorPvP = 0; // 1 is AI 0 is PVP. please dont delete

  int FillerValue = -10; // to use for kingcheck outside of checkmove
  int check;

	//functions for the main menu - right now it doesnt really do anything
	jungkookie = MainMenuState1();
 if (jungkookie == -1){
 gamestate = 0;}
 if (gamestate == 1){
   AIorPvP = MainMenuState2();
    if (AIorPvP == -1){
       gamestate = 0;}
  	playercolor = MainMenuState3();
     if (playercolor == -1){
         gamestate =0;}}

  if (gamestate != 0){
  printf("%s", initial_message);
	//actual chess game starts here
	Chess_board_default();
	Chess_pieces_default();
	Get_board();
	Print_board();

if (playercolor != Player_Turn_Color){
  printf("%s must wait for %s to make a move\n", Colors[playercolor], Colors[Player_Turn_Color]);
  }}

	while (gamestate == 1){

 if (playercolor == Player_Turn_Color|| AIorPvP ==0){ // allows PvP to function but also allowing it to be color turn based


check = kingcheck(FillerValue, FillerValue, Player_Turn_Color);

if (check==1){
    printf("\n%s king is in check \n", Colors[Player_Turn_Color]);}

if (checkmate(check, Player_Turn_Color )==1){
  printf("%s", winning_message);
  gamestate = 0;
  continue;
}


  while (userinputStage == 1){

     printf("%s's turn\n", Colors[Player_Turn_Color]);

   if (jungkookie == 1){
    JungKook();
	}
  	//need to scan for the type of piece
		printf("Choose the piece you want to move.");
		//in an array, use Array instead of &
		scanf("%s",CurPositionText);
    printf("%s", CurPositionText);
    if (('a' <= CurPositionText[0] && 'h' >= CurPositionText[0]) &&
    '1' <= CurPositionText[1] && '8' >= CurPositionText[1] && strlen(CurPositionText)==2){
		//converter - converts input into a number
		for (count1=0; count1<8; count1++){
	    if (CurPositionText[0] == letters[count1]) {
	      firstChar = 'a' - 97 + count1;
	    }
	  }

	  for (count2=0; count2<8; count2++){
	    if (CurPositionText[1] == numbers[count2]) {
	      secondChar = '8' - (8*count2) ;
	    }
	  }
		CurPosition = firstChar + secondChar;

    // checks the current piece matches the turn color
    if (Pieces[CurPosition].Player.Color == Player_Turn_Color){
        userinputStage = 0;}
        else{
        printf("wrong color piece\n please try again \n");
    }}
    else{printf("invalid selection: move format is File (lower case letter a-f) Rank (1-8) ex: a5\n");
    printf("please try again:\n");}}

		//test statements to see what piece is what
		printf("Moving piece %c%c\n", Pieces[CurPosition].Name[0],Pieces[CurPosition].Name[1]);
		printf("The Color and type of this piece is a %s %s\n", Colors[Pieces[CurPosition].Player.Color], pieceNames[Pieces[CurPosition].TYPE]);

    userinputStage = 1; // second userinput stage is true

    while (userinputStage == 1){
		printf("Choose the place to move.");
		scanf("%s",NewPositionText);
   
   
//---------------------------------------------------------------------------------------------------------

if (strcmp(CurPositionText, "scan")==0){
	
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
}
//----------------------------------------------------------------------------------------------------------

   
if (('a' <= NewPositionText[0] && 'h' >= NewPositionText[0])&&
    '1' <= NewPositionText[1] && '8' >= NewPositionText[1] && strlen(NewPositionText)==2){

		//converter - converts input into a number
		for (count1=0; count1<8; count1++){
	    if (NewPositionText[0] == letters[count1]) {
	      firstChar = 'a' - 97 + count1;
	    }
	  }

	  for (count2=0; count2<8; count2++){
	    if (NewPositionText[1] == numbers[count2]) {
	      secondChar = '8' - (8*count2) ;
	    }
	  }
		NewPosition = firstChar + secondChar;
    userinputStage = 0;}
    else{printf("invalid selection: move format is File (lower case letter a-f) Rank (1-8) ex: a5\n");
    printf("please try again:\n");}}


		//check validity----------------------------------------------------------------------------------------
    while (CheckMove(CurPosition,NewPosition,1) == 0){
			printf("Invalid move! Choose the piece you want to move again.\n");
      userinputStage=1; // we need this to take in a new piece
    while (userinputStage == 1){
       printf("%s's turn\n", Colors[Player_Turn_Color]);

   if (jungkookie == 1){
      // jungkook AI call}
}
		//need to scan for the type of piece
		printf("Choose the piece you want to move.");

		//in an array, use Array instead of &
		scanf("%s",CurPositionText);
    if (('a' <= CurPositionText[0] && 'h' >= CurPositionText[0]) &&
    '1' <= CurPositionText[1] && '8' >= CurPositionText[1] && strlen(CurPositionText)==2){
//---------------------------------------------------------------------------------------------------
		//converter - converts input into a number
		for (count1=0; count1<8; count1++){
	    if (CurPositionText[0] == letters[count1]) {
	      firstChar = 'a' - 97 + count1;
	    }
	  }

	  for (count2=0; count2<8; count2++){
	    if (CurPositionText[1] == numbers[count2]) {
	      secondChar = '8' - (8*count2) ;
	    }
	  }
		CurPosition = firstChar + secondChar;
	//---------------------------------------------------------------------------------------------------

    // checks the current piece matches the turn color
    if (Pieces[CurPosition].Player.Color == Player_Turn_Color){
        userinputStage = 0;}
        else{
        printf("wrong color piece\n please try again \n");
    }}
    else{printf("invalid selection: \n move format is File (lower case letter a-f) Rank (1-8) ex: a5\n");
    printf("please try again:\n");}}

    		//test statements to see what piece is what
		printf("Moving piece %c%c\n", Pieces[CurPosition].Name[0],Pieces[CurPosition].Name[1]);
		printf("The Color and type of this piece is a %s %s\n", Colors[Pieces[CurPosition].Player.Color], pieceNames[Pieces[CurPosition].TYPE]);

    userinputStage = 1; // second userinput stage is true

    while (userinputStage == 1){
		printf("Choose the place to move.");
		scanf("%s",NewPositionText);
if (('a' <= NewPositionText[0] && 'h' >= NewPositionText[0])&&
    '1' <= NewPositionText[1] && '8' >= NewPositionText[1] && strlen(NewPositionText)==2){

		//converter - converts input into a number
		for (count1=0; count1<8; count1++){
	    if (NewPositionText[0] == letters[count1]) {
	      firstChar = 'a' - 97 + count1;
	    }
	  }

	  for (count2=0; count2<8; count2++){
	    if (NewPositionText[1] == numbers[count2]) {
	      secondChar = '8' - (8*count2) ;
	    }
	  }
		NewPosition = firstChar + secondChar;
    userinputStage = 0;}
    else{printf("invalid selection: move format is File (lower case letter a-f) Rank (1-8) ex: a5\n");
    printf("please try again:\n");}}
		}
		Move_Piece(CurPosition, NewPosition);
		logfile(CurPosition,NewPosition);
    Castling(NewPosition);
    enpassant_risk_pawn_location = ENPASSANT(enpassant_risk_pawn_location, NewPosition);
    Promotion(NewPosition,0);
		//Get_board();
}
else{Player_Turn_Color = !Player_Turn_Color; // changes from white to black to allow the player to play
}
		//This part is the AI moving the piece - testing the AI out by moving pawns
if (AIorPvP ==1){
check = kingcheck(FillerValue, FillerValue, !Player_Turn_Color);
if (check==1){
    printf("\n%s king is in check \n", Colors[!Player_Turn_Color]);}

if (checkmate(check, !Player_Turn_Color )==1){
		Get_board();
		Print_board();
  printf("%s", winning_message);
  gamestate = 0;
  continue;
}
		AIMove();}
		Get_board();
		Print_board();
if (AIorPvP ==0){ // we need to to switch between ai or pvp mode
    Player_Turn_Color = !Player_Turn_Color;} // 0 to 1 black white;
    userinputStage = 1;


	}
  printf("%s",end_message);
	return 0;
}
