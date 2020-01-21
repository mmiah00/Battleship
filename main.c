#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "gameplay.c"

int main () {
  introscreen ();


  struct gameBoard p1;
  struct gameBoard *pointer1 = &p1;
  pointer1->player = 1;
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      pointer1->board[r][c] = 0;//0 represents water, -1 represents a ship, 1 represents a hit, 2 represents a miss
    }
  }

  struct gameBoard p2;
  struct gameBoard *pointer2 = &p2;
  pointer2->player = 2;
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      pointer2->board[r][c] = 0;//0 represents water, -1 represents a ship, 1 represents a hit, 2 represents a miss
    }
  }

  //filling board with ships
  int ship1placed = 0; //two coords long
  int ship2placed = 0; //three coords long
  int ship3placed = 0; //three coords long
  int ship4placed = 0; //four coords long
  int ship5placed = 0; //five coords long
  char input[1000];
  printf("The command for placing a ship is 'place x y 1-5 HorV'\n");
  printf("Ex:place 0 0 1 h\n");
  while (ship1placed == 0 || ship2placed == 0 || ship3placed == 0 || ship4placed == 0 || ship5placed == 0){//only continues to gameplay if all ships are placed
    printf("Please place your ships to continue:");
    fgets(input,sizeof(input), stdin);
    input[strlen(input) - 1] = '\0';
    char ** args = parse_args(input);
    if (args[0] != NULL && args[1] != NULL && args[2] != NULL && args[3] != NULL && args[4] != NULL && strcmp(args[0], "place") == 0){
      int xcoord = atoi(args[1]);
      int ycoord = atoi(args[2]);
      int shipType = atoi(args[3]);
      //command is "$place xcoord ycoord shiptype verticalorhorizontal"
      if (placeShip(ycoord, xcoord, shipType, args[4], p1.board, pointer1) == 0){ //p2.board if the current player is player 2
        printf("Ship placed unsuccessfully. Try again :(\n");
        display("ally", 1, p1, p2);
      }
      else{
        printf("Ship placed successfully :)\n");
        display("ally", 1, p1, p2);
        if (shipType == 1){
          //printf("runned\n");
          ship1placed = 1;
        }
        if (shipType == 2){
          //printf("runned\n");
          ship2placed = 1;
        }
        if (shipType == 3){
          //printf("runned\n");
          ship3placed = 1;
        }
        if (shipType == 4){
          ship4placed = 1;
        }
        if (shipType == 5){
          ship5placed = 1;
        }
      }
    }
    free(args);
  }

  //gameplay commands
  printf("Enter 'help' for commands\n");
    int gameFinished = 0;//0 is unfinished
    char command[1000];
    int running = 1; //true
    int turnEnded = 0; //false
    while (running == 1){
      printf("Receiving data from other player\n");
      turnEnded = 0;
      while (turnEnded == 0){
        gameFinished = finished(pointer1, pointer2);
        if (gameFinished == 0){//game is unfinished
          printf("Awaiting your next command:");
          fgets(command, sizeof(command), stdin);
          command[strlen(command) - 1] = '\0';
          char ** args2 = parse_args(command);
          if (strcmp(args2[0], "exit") == 0){
            running = 0;
            turnEnded = 1;
            return 0;
          }
          else{
            int status = executeCommand(args2, 2, p1, p2, pointer1, pointer2);
            if (status == 1){
              turnEnded = 1;
              printf("Your turn ended\n");
            }
          }
          free(args2);
        }
        else{
          if (gameFinished == 1){
            printf("Player 1 wins wooooooooooooooooooo\n\n");
            turnEnded = 1;
            running = 0;
          }
          else{
            printf("Player 2 wins wooooooooooooooooooo\n\n");
            turnEnded = 1;
            running = 0;
          }
        }
      }
      printf("Sending data to other player\n\n");
    }
    //while (exported == 0){//only stops if history.txt is sent somewhere
    printf("Where do you want to export the history file?\nEnter . to leave it here:");
    char stuff[1000];
    fgets(stuff,sizeof(stuff), stdin);
    char ** argy = parse_args(stuff);
    exportHistory(argy[0]);
    //}

    return 0;
  }
