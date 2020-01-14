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

void introscreen () { //thank you patorjk.com for the ASCII art
  printf ("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗     \n");
  printf ("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗    \n");
  printf ("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║    \n");
  printf ("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║    \n");
  printf ("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝    \n");
  printf (" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝     \n");
  printf ("                                                                                        \n");
  printf ("    ██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗        \n");
  printf ("    ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗       \n");
  printf ("    ██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██████╔╝       \n");
  printf ("    ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██╔═══╝        \n");
  printf ("    ██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██║            \n");
  printf ("    ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝            \n");

  printf("\n\n");
  printf("                                )___( \n");
  printf("                          _______/__/_\n");
  printf("                 ___     /===========|   ___\n");
  printf("____       __   [\\\\]___/____________|__[///]   __\n");
  printf("\\   \\_____[\\]__/___________________________\\__[//]___\n");
  printf(" \40A                                                 |\n");
  printf("  \\                                                  /\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf ("\n\n");

  /*
  printf ("██████╗ ██████╗ ███████╗███████╗███████╗    ███████╗██████╗  █████╗  ██████╗███████╗    \n");
  printf ("██╔══██╗██╔══██╗██╔════╝██╔════╝██╔════╝    ██╔════╝██╔══██╗██╔══██╗██╔════╝██╔════╝    \n");
  printf ("██████╔╝██████╔╝█████╗  ███████╗███████╗    ███████╗██████╔╝███████║██║     █████╗      \n");
  printf ("██╔═══╝ ██╔══██╗██╔══╝  ╚════██║╚════██║    ╚════██║██╔═══╝ ██╔══██║██║     ██╔══╝      \n");
  printf ("██║     ██║  ██║███████╗███████║███████║    ███████║██║     ██║  ██║╚██████╗███████╗    \n");
  printf ("╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝    ╚══════╝╚═╝     ╚═╝  ╚═╝ ╚═════╝╚══════╝    \n");
  printf ("████████╗ ██████╗      ██████╗ ██████╗ ███╗   ██╗████████╗██╗███╗   ██╗██╗   ██╗███████╗\n");
  printf ("╚══██╔══╝██╔═══██╗    ██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██║████╗  ██║██║   ██║██╔════╝\n");
  printf ("   ██║   ██║   ██║    ██║     ██║   ██║██╔██╗ ██║   ██║   ██║██╔██╗ ██║██║   ██║█████╗  \n");
  printf ("   ██║   ██║   ██║    ██║     ██║   ██║██║╚██╗██║   ██║   ██║██║╚██╗██║██║   ██║██╔══╝  \n");
  printf ("   ██║   ╚██████╔╝    ╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║██║ ╚████║╚██████╔╝███████╗\n");
  printf ("   ╚═╝    ╚═════╝      ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝\n");
  */
/*
  printf(" .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.\n");
  printf("| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
  printf("| |   ______     | || |      __      | || |  _________   | || |  _________   | || |   _____      | || |  _________   | |\n");
  printf("| |  |_   _ \\    | || |     /  \\     | || | |  _   _  |  | || | |  _   _  |  | || |  |_   _|     | || | |_   ___  |  | |\n");
  printf("| |    | |_) |   | || |    / /\\ \\    | || | |_/ | | \\_|  | || | |_/ | | \\_|  | || |    | |       | || |   | |_  \\_|  | |\n");
  printf("| |    |  __'.   | || |   / ____ \\   | || |     | |      | || |     | |      | || |    | |   _   | || |   |  _|  _   | |\n");
  printf("| |   _| |__) |  | || | _/ /    \\ \\_ | || |    _| |_     | || |    _| |_     | || |   _| |__/ |  | || |  _| |___/ |  | |\n");
  printf("| |  |_______/   | || ||____|  |____|| || |   |_____|    | || |   |_____|    | || |  |________|  | || | |_________|  | |\n");
  printf("| |              | || |              | || |              | || |              | || |              | || |              | |\n");
  printf("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
  printf(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n");
  printf("                     .----------------.  .----------------.  .----------------.  .----------------.                     \n");
  printf("                    | .--------------. || .--------------. || .--------------. || .--------------. |                    \n");
  printf("                    | |    _______   | || |  ____  ____  | || |     _____    | || |   ______     | |                    \n");
  printf("                    | |   /  ___  |  | || | |_   ||   _| | || |    |_   _|   | || |  |_   __ \\   | |                    \n");
  printf("                    | |  |  (__ \\_|  | || |   | |__| |   | || |      | |     | || |    | |__) |  | |                    \n");
  printf("                    | |   '.___`-.   | || |   |  __  |   | || |      | |     | || |    |  ___/   | |                    \n");
  printf("                    | |  |`\\____) |  | || |  _| |  | |_  | || |     _| |_    | || |   _| |_      | |                    \n");
  printf("                    | |  |_______.'  | || | |____||____| | || |    |_____|   | || |  |_____|     | |                    \n");
  printf("                    | |              | || |              | || |              | || |              | |                    \n");
  printf("                    | '--------------' || '--------------' || '--------------' || '--------------' |                    \n");
  printf("                     '----------------'  '----------------'  '----------------'  '----------------'      ");
  */
}

struct gameBoard{
  int player; //board of the specified player
  int board[8][8]; //ships only be visible to the owner of this board. otherwise it will look like an empty spot
};

struct coordinate  {
  int x,y;
};


int isValid(int xcoord, int ycoord, int shipSize, char * HorV, int board[8][8] ){
  if (strcmp(HorV, "vertical") == 0){//check vertically
    for (int r = xcoord; r < 8 && shipSize != 0; r++){
      if (board[r][ycoord] == 0){//if spot is empty
        shipSize--;//one coord of ship is valid
      }
    }
    if (shipSize == 0){
      return 1; //it is valid
    }
    else{
      return 0; //ship is too long to be placed here
    }
  }
  else if (strcmp(HorV, "horizontal") == 0){//check horizontally
    for (int c = ycoord; c < 8 && shipSize != 0; c++){
      if (board[xcoord][c] == 0){
        shipSize--;
      }
    }
    if (shipSize == 0){
      return 1; //it is valid
    }
    else{
      return 0; //ship is too long to be placed here
    }
  }
  else{
    return 0;//invalid arg
  }
}
int placeShip(int xcoord, int ycoord, int shipType, char * HorV, int board[8][8]){
  if (shipType < 1 && shipType > 5 && xcoord > 7 && xcoord < 0 && ycoord > 7 && ycoord < 0){//there are only 5 types of ships
    return 0;
  }
  int shipSize = 0;
  if (shipType == 1){
    shipSize = 2;
  }
  if (shipType == 2){
    shipSize = 3;
  }
  if (shipType == 3){
    shipSize = 3;
  }
  if (shipType == 4){
    shipSize = 4;
  }
  if (shipType == 5){
    shipSize = 5;
  }
  if (isValid(xcoord, ycoord, shipSize, HorV, board) == 0){//returns 0 if ship can't be placed
    printf("Invalid coordinates\n");
    return 0;//false
  }
  else{//ship location is valid
    if (strcmp(HorV, "vertical") == 0){
      for (int r = xcoord; shipSize != 0; r++){
        board[r][ycoord] = 1;
        shipSize--;
      }
    }
    else if (strcmp(HorV, "horizontal") == 0){
      for (int c = ycoord; shipSize != 0; c++){
        board[xcoord][c] = 1;
        shipSize--;
      }
    }
    return 1;//successfully placed
  }
}

int display(char * status, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board){
  if (strcmp(status, "ally") == 0){//display your board
    if (currentPlayer == 1){//if player 1 display p1Board
      for (int r = 0; r < 8; r++){
        for (int c = 0; c < 8; c++){
          if (p1Board.board[r][c] == 0){//0 represents water
            printf("~");//water
          }
          if (p1Board.board[r][c] == 1){//1 represents a ship
            printf("H");//ship
          }
          if (p1Board.board[r][c] == 2){//2 represents a successful hit by the enemy
            printf("O");//hit
          }
          if (p1Board.board[r][c] == 3){//3 represents a missed hit by the enemy
            printf("X");//miss
          }
        }
        printf("\n");
      }
      return 1;
    }
    else{//if player 2 display p2Board
      for (int r = 0; r < 8; r++){
        for (int c = 0; c < 8; c++){
          if (p2Board.board[r][c] == 0){//0 represents water
            printf("~");//water
          }
          if (p2Board.board[r][c] == 1){//1 represents a ship
            printf("H");//ship
          }
          if (p2Board.board[r][c] == 2){//2 represents a successful hit by the enemy
            printf("O");//hit
          }
          if (p2Board.board[r][c] == 3){//3 represents a missed hit by the enemy
            printf("X");//miss
          }
        }
        printf("\n");
      }
      return 1;
    }
  }
  else if (strcmp(status, "enemy") == 0){//display enemy board
    if (currentPlayer == 1){//if player 1 display p2Board
      for (int r = 0; r < 8; r++){
        for (int c = 0; c < 8; c++){
          if (p2Board.board[r][c] == 0){//0 represents water
            printf("~");//water
          }
          if (p2Board.board[r][c] == 1){//1 represents a ship but you can't see enemy ships
            printf("~");//hidden ship
          }
          if (p2Board.board[r][c] == 2){//2 represents a successful hit by the enemy
            printf("O");//hit
          }
          if (p2Board.board[r][c] == 3){//3 represents a missed hit by the enemy
            printf("X");//miss
          }
        }
        printf("\n");
      }
      return 1;
    }
    else{//if player 2 display p1Board
      for (int r = 0; r < 8; r++){
        for (int c = 0; c < 8; c++){
          if (p1Board.board[r][c] == 0){//0 represents water
            printf("~");//water
          }
          if (p1Board.board[r][c] == 1){//1 represents a ship but you can't see enemy ships
            printf("~");//hidden ship
          }
          if (p1Board.board[r][c] == 2){//2 represents a successful hit by the enemy
            printf("O");//hit
          }
          if (p1Board.board[r][c] == 3){//3 represents a missed hit by the enemy
            printf("X");//miss
          }
        }
        printf("\n");
      }
      return 1;
    }
  }
  else{
    return 0;//incorrect arg
  }
}

int attack(int xcoord, int ycoord, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board){
  if (currentPlayer == 1){
    if (p2Board.board[xcoord][ycoord] == 0){//there is nothing here but h2o
      //missed
      p2Board.board[xcoord][ycoord] == 3;//3 indicates a miss
      return 0;//unsuccessful attack
    }
    else if (p2Board.board[xcoord][ycoord] == 1){//there is a ship here
      p2Board.board[xcoord][ycoord] == 2;//2 indicates a successful hit
      return 1;//successful attack
    }
    else{//everything else if it isn't 0 or 1 is either a 2 or a 3
      printf("You already attacked this position and just wasted your turn. haha\n");
      return 0;//unsuccessful attack
    }
  }
  if (currentPlayer == 2){
    if (p1Board.board[xcoord][ycoord] == 0){//there is nothing here but h2o
      //missed
      p1Board.board[xcoord][ycoord] == 3;//3 indicates a miss
      return 0;//unsuccessful attack
    }
    else if (p1Board.board[xcoord][ycoord] == 1){//there is a ship here
      p1Board.board[xcoord][ycoord] == 2;//2 indicates a successful hit
      return 1;//successful attack
    }
    else{//everything else if it isn't 0 or 1 is either a 2 or a 3
      printf("You already attacked this position and just wasted your turn. haha\n");
      return 0;//unsuccessful attack
    }
  }
}

int executeCommand(char ** command, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board){
  if (strcmp(command[0], "help") == 0){
    printf("Instructions\n");
    printf("...\n");
  }
  else if (strcmp(command[0], "history") == 0){
    printf("Displaying game history:\n");
    //history ();
  }
  else if (strcmp(command[0], "display") == 0 && strcmp(command[1], "ally") == 0){
    printf("Displaying your board and ships\n");
    display("ally", currentPlayer, p1Board, p2Board);
  }
  else if (strcmp(command[0], "display") == 0 && strcmp(command[1], "enemy") == 0){
    printf("Displaying enemy's board\n");
    display("enemy", currentPlayer, p1Board, p2Board);
  }
  else if (strcmp(command[0], "attack") == 0){
    int xcoord = atoi(command[1]);
    int ycoord = atoi(command[2]);
    if (xcoord > 7 || xcoord < 0 || ycoord > 7 || ycoord < 0){

    }
    else{
      int status = attack(xcoord, ycoord, currentPlayer, p1Board, p2Board);
      if (status == 1){
        printf("Ship found and attacked at this location!\n");
      }
      else{
        printf("Unsuccessful attack :(\n");
      }
    }
  }
  return 0;
}

char ** parse_args( char * line ){
  char ** var = malloc(sizeof(char *) * 5);
  int size;
  for (size = 0; size < 5; size++){
    var[size] = strsep(&line, " ");
  }
  var[size] = NULL;
  return var;
}

int main () {
  introscreen ();
  int running = 1;

  struct gameBoard p1;
  p1.player = 1;
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      p1.board[r][c] = 0;//0 represents water, -1 represents a ship, 1 represents a hit, 2 represents a miss
    }
  }

  struct gameBoard p2;
  p2.player = 2;
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      p2.board[r][c] = 0;//0 represents water, -1 represents a ship, 1 represents a hit, 2 represents a miss
    }
  }

  //int historyFile = open("history.txt", O_CREAT, 0644);

  //filling board with ships
  int ship1placed = 0; //two coords long
  int ship2placed = 0; //three coords long
  int ship3placed = 0; //three coords long
  int ship4placed = 0; //four coords long
  int ship5placed = 0; //five coords long
  char input[1000];
  while (ship1placed == 0 || ship2placed == 0 || ship3placed == 0 || ship4placed == 0 || ship5placed == 0){//only continues to gameplay if all ships are placed
    printf("Please place your ships to continue\n");
    fgets(input,sizeof(input), stdin);
    input[strlen(input) - 1] = '\0';
    char ** args = parse_args(input);
    if (strcmp(args[0], "place") == 0){
      int xcoord = atoi(args[1]);
      int ycoord = atoi(args[2]);
      int shipType = atoi(args[3]);
      //command is "$place xcoord ycoord shiptype verticalorhorizontal"
      if (placeShip(xcoord, ycoord, shipType, args[4], p1.board) == 0){ //p2.board if the current player is player 2
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
  char command[1000];
  while (running){
    printf("Awaiting your next command:");
    fgets(command, sizeof(command), stdin);
    command[strlen(command) - 1] = '\0';
    char ** args2 = parse_args(command);
    //printf("Your command is %s\n\n", command);
    if (strcmp(args2[0], "exit") == 0){
      running = 0;
    }
    else{
      executeCommand(args2, 1, p1, p2);
    }
    free(args2);
  }
  return 0;
}
