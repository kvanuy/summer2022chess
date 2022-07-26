#include <stdio.h>
#include "gamestateflow.h"
int MainMenuState = 1;

char JungkookMode = 7;
char PlayerGameOptionState = 5;
char PlayerColorChoiceState = 2;

int MainChessGamereturn1;
int MainChessGamereturn2;
int MainChessGamereturn3;

int MainMenuState1OnSwitch = 0;
int MainMenuState2OnSwitch = 0;
int MainMenuState3OnSwitch = 0;





int MainMenuState1() {
//printf("Psuedo code for 4 GameStates\n\n");
while (MainMenuState1OnSwitch == 0){
  printf("Welcome to Jungkook Chess!\n");
  printf("To quit at any time before the game starts, please enter 'x' to exit\n");
  printf("Do you want to enable Jungkook mode?\n1 for yes\n0 for no\n");
  scanf(" %c", &JungkookMode);
  if (JungkookMode -48 == 1){
      printf("\nJungkook Mode enabled\n");
      MainMenuState1OnSwitch++;
      MainChessGamereturn1 = 1;
    }
  else if (JungkookMode -48 == 0){
      printf("\nJungkook Mode is not enabled\n");
      MainMenuState1OnSwitch++;
      MainChessGamereturn1 = 0;
    }
    else if (JungkookMode == 120){
      MainMenuState1OnSwitch++;
      MainChessGamereturn1 = -1; }// quit
    
  else {
      printf("\ninvalid response. please try again\n");
      MainMenuState1OnSwitch = 0;
    }
  }
  return MainChessGamereturn1;
}

//----------------------------------------------------------
int MainMenuState2() {
while (MainMenuState2OnSwitch == 0){
        printf("Please choose game option:\n0 for Player v Player\n1 for AI \n");
        scanf(" %c", &PlayerGameOptionState);
        if (PlayerGameOptionState-48 == 0){
            printf("\nChess game will be Player v Player\n");
            MainMenuState2OnSwitch++;
            MainChessGamereturn2 = 0;
        }
        else if (PlayerGameOptionState-48 == 1){
            printf("\nChess game will be Player v AI\n");
            MainMenuState2OnSwitch++;
            MainChessGamereturn2 = 1;
        }
          else if (PlayerGameOptionState == 120){
          MainMenuState1OnSwitch++;
      MainChessGamereturn2 = -1; }
        else {
            printf("\ninvalid response. Please try again.\n");
            MainMenuState2OnSwitch = 0;
        }
      }
      return MainChessGamereturn2;
}
//----------------------------------------------------------
int MainMenuState3() {
    while ((MainMenuState3OnSwitch == 0)){
        printf("Please choose which color to play as:\n0 for black\n1 for white\n");
        scanf(" %c", &PlayerColorChoiceState);
        if (PlayerColorChoiceState-48 == 0){
            printf("\nPlayer chose black\n");
            printf("\nBeginning Chess Game! \n");
            MainMenuState3OnSwitch++;
            MainChessGamereturn3 = 0;

        }
        else if (PlayerColorChoiceState-48 == 1){
            printf("\nPlayer chose white\n");
            printf("\nBeginning Chess Game! \n");
            MainMenuState3OnSwitch++;
            MainChessGamereturn3 = 1;
        }
        else if (PlayerColorChoiceState == 120){
          MainChessGamereturn3 = -1;}
        else{
            printf("\ninvalid response. Please try again.\n");
            MainMenuState3OnSwitch = 0;
        }
      }
return MainChessGamereturn3;
}
//----------------------------------------------------------
