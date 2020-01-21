#include "battleship.h"

struct coordinate {
  int x,y;
};

struct gameBoard{
  int player; //board of the specified player
  int board[8][8]; //ships only be visible to the owner of this board. otherwise it will look like an empty spot
};

struct status_message
{
    int type;
    /* 0 = MISS
     * 1 = HIT
     * 2 = OK
     * 3 = FINISH
     */
    int response;

};


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
}


void display_my_board (struct gameBoard g){
  printf ("      0 1 2 3 4 5 6 7\n\n");
  int r,c;
  for (int r = 0; r < 8; r++){
  printf("   %d  ", r);
    for (int c = 0; c < 8; c++){
      if (g.board[r][c] == 0){//0 represents water
        printf("~ ");//water
      }
      if (g.board[r][c] == 1){//1 represents a ship
        printf("H ");//ship
      }
      if (g.board[r][c] == 2){//2 represents a successful hit by the enemy
        printf("O ");//hit
      }
      if (g.board[r][c] == 3){//3 represents a missed hit by the enemy
        printf("X ");//miss
      }
    }
    printf("\n");
  }
  printf("\n");
}

char ** parse_args( char * line ){//parsing command args
  char ** var = malloc(sizeof(char *) * 5);
  int size;
  for (size = 0; size < 5; size++){
    var[size] = strsep(&line, " ");
  }
  var[size] = NULL;
  return var;
}

int isValid(int xcoord, int ycoord, int shipSize, char * HorV, int board[8][8] ){//checks if a ship can be placed here
  if (strcmp(HorV, "v") == 0){//check vertically
    int stop1 = 0;
    for (int r = xcoord; r < 8 && (shipSize != 0 && stop1 == 0); r++){
      if (board[r][ycoord] != 0){//if spot is empty
        stop1 = 1;
      }
      shipSize--;
    }
    if (stop1 == 0){
      return 1; //it is valid
    }
    else{
      return 0; //ship is too long to be placed here
    }
  }
  else if (strcmp(HorV, "h") == 0){//check horizontally
    int stop2 = 0;
    for (int c = ycoord; c < 8 && (shipSize != 0 && stop2 == 0); c++){
      if (board[xcoord][c] != 0){
        stop2 = 1;
      }
      shipSize--;
    }
    if (stop2 == 0){
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

int placeShip(int xcoord, int ycoord, int shipType, char * HorV, int board[8][8], struct gameBoard * pointer){//places a ship at the xy
  if (shipType < 1 && shipType > 5 && xcoord > 7 && xcoord < 0 && ycoord > 7 && ycoord < 0){//there are only 5 types of ships
    printf("Coordinates are out of bounds \n");
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
    if (strcmp(HorV, "v") == 0){
      for (int r = xcoord; shipSize != 0; r++){
        pointer->board[r][ycoord] = 1;
        shipSize--;
      }
    }
    else if (strcmp(HorV, "h") == 0){
      for (int c = ycoord; shipSize != 0; c++){
        pointer->board[xcoord][c] = 1;
        shipSize--;
      }
    }
    return 1;//successfully placed
  }
}

int attack(int xcoord, int ycoord, int currentPlayer,struct gameBoard * p1Board, struct gameBoard * p2Board){//attacks a coordinate
  //FILE *tile = fopen("history.txt", "a");
  if (currentPlayer == 1){
    if (p2Board->board[xcoord][ycoord] == 0){//there is nothing here but h2o
      p2Board->board[xcoord][ycoord] = 3;//3 indicates a miss
      return 0;//unsuccessful attack
    }
    else if (p2Board->board[xcoord][ycoord] == 1){//there is a ship here
      p2Board->board[xcoord][ycoord] = 2;//2 indicates a successful hit
      return 1;//successful attack
    }
    else{//everything else if it isn't 0 or 1 is either a 2 or a 3
      printf("You already attacked this position and just wasted your turn. haha\n");
      return 0;//unsuccessful attack
    }
  }
  if (currentPlayer == 2){
    if (p1Board->board[xcoord][ycoord] == 0){//there is nothing here but h2o
      p1Board->board[xcoord][ycoord] = 3;//3 indicates a miss
      return 0;//unsuccessful attack
    }
    else if (p1Board->board[xcoord][ycoord] == 1){//there is a ship here
      p1Board->board[xcoord][ycoord] = 2;//2 indicates a successful hit
      return 1;//successful attack
    }
    else{//everything else if it isn't 0 or 1 is either a 2 or a 3
      printf("You already attacked this position and just wasted your turn. haha\n");
      return 0;//unsuccessful attack
    }
  }
}

int display(char * status, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board){//displays a board based on given args
  if (strcmp(status, "ally") == 0){//display your board
    if (currentPlayer == 1){//if player 1 display p1Board
      display_my_board(p1Board);
      return 1;
    }
    else{//if player 2 display p2Board
      display_my_board(p2Board);
      return 1;
    }
  }
  else if (strcmp(status, "enemy") == 0){//display enemy board
    if (currentPlayer == 1){//if player 1 display p2Board
      display_my_board(p2Board);
      return 1;
    }
    else{//if player 2 display p1Board
      display_my_board(p1Board);
      return 1;
    }
  }
  else{
    return 0;//incorrect arg
  }
}

int displayHistory(){//display game history by catting history.txt
  int id = fork();
  if (id == 0){
    char *args[] = {"cat", "history.txt", 0};
    int a = execvp(args[0], args);
  }
  else{
    wait(0);
  }
  return 1;
}

void exportHistory(char * path){//exports the history.txt to the specified path after someone wins
  int id = fork();
  if (id == 0){
    char *args[4] = {"mv", "history.txt", path, 0};
    //strcpy(args[2], path);
    int a = execvp(args[0], args);
  }
  else{
    wait(0);
  }
}

int finished(struct gameBoard * pointer){//checks if the game is finish by checking the board and returns winning player
  int i, j;

  for(i=0; i<8; i++)
    for(j=0; j<8; j++)
        if (pointer->board[i][j] == 1) //Found ship
            return 1;

            return 0;
}


int executeCommand(char ** command, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board, struct gameBoard *pointer1, struct gameBoard * pointer2){//calls the gameplay functions
  if (strcmp(command[0], "help") == 0){
    printf("Instructions\n");
    printf("...\n");
    printf("To display a board type 'display enemyOrAlly'. Ex:display ally\n");
    printf("To see game history type 'history'\n\n");
  }
  else if (strcmp(command[0], "history") == 0){
    printf("Displaying game history:\n");
    displayHistory();
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
  return 0;
}
