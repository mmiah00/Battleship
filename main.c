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

int display(int user, struct gameBoard p1Board, struct gameBoard p2Board){
  if (user == p1Board.player){
    printf("printing your board\n");
    for (int r = 0; r < 8; r++){
      for (int c = 0; c < 8; c++){
        if (p1Board.board[r][c] == 0){
          printf("~");
        }
      }
      printf("\n");
    }
  }
  else{
    printf("printing enemy's board\n");
  }
}

int executeCommand(char * command, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board){
  if (strcmp(command, "help") == 0){
    printf("Instructions\n");
    printf("...\n");
  }
  else if (strcmp(command, "history") == 0){
    printf("Displaying game history:\n");
    //history ();
  }
  else if (strcmp(command, "display ally") == 0){
    printf("Displaying your board and ships\n");
  }
  else if (strcmp(command, "display enemy") == 0){
    printf("Displaying enemy's board\n");
  }
  return 0;
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
  char command[1000];
  while (running){
    printf("Awaiting your next command:");
    fgets(command, sizeof(command), stdin);
    command[strlen(command) - 1] = '\0';
    printf("Your command is %s\n\n", command);
    if (strcmp(command, "exit") == 0){
      running = 0;
    }
    else{
      executeCommand(command, -1, p1, p2);
    }
  }
  return 0;
}
