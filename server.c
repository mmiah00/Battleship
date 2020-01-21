#include "networking.h"
#include "battleship.c"

struct gameBoard server_board;
struct gameBoard client_board;



int main() {
  // Messages settings
  struct status_message *s_msg;
  struct coordinate *cor;

  // The sockets
  int listen_socket;
  int client_socket;



  server_board.player = 1;
  struct gameBoard *pointer1 = &server_board;
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
    pointer1->board[r][c] = 0;//0 represents water, -1 represents a ship, 1 represents a hit, 2 represents a miss
    }
  }

  client_board.player = 2;// copy to this
  struct gameBoard *pointer2 = &client_board;
  pointer2->player = 2;
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      pointer2->board[r][c] = 0;//0 represents water, -1 represents a ship, 1 represents a hit, 2 represents a miss
    }
  }

  //set of file descriptors to read from
  fd_set read_fds;

  listen_socket = server_setup();
  printf ("Waiting for other player... \n");

  client_socket = server_connect(listen_socket);

  printf ("Let's place your ships!\n\n");



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
      if (placeShip(ycoord, xcoord, shipType, args[4], server_board.board, pointer1) == 0){ //p2.board if the current player is player 2
        printf("Ship placed unsuccessfully. Try again :(\n");
        display("ally", 1,server_board, client_board);
      }
      else{
        printf("Ship placed successfully :)\n");
        display("ally", 1, server_board, client_board);
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




  printf("\nShips ready!\n");
  // ------------------------------------------------------------------------

  printf ("Waiting for other player... \n");

  s_msg = malloc(sizeof(s_msg));

  recv(client_socket, s_msg, sizeof(s_msg), 0);

  if (s_msg->response != 2)
  {
      exit(1);
  }
  free(s_msg);

  system("clear");


    // ------------------------------------------------------------------------
    // Game starts
while(1) {
    // Server attacks -----------------------------------------------------
    int r, c;
//    display ("ally", server_board.player, server_board, client_board);
printf("DISPLAYING MY BOARD\n");
display_my_board(server_board);
printf("\n");
printf("DISPLAYING THEIR BOARD\n");
display_my_board(client_board);

    char input [1000];
    char commands[1000];
    char ** cords;
    printf("Your turn to attack\n");
    while(1){
    printf ("Type in your 'attack' or 'command': ");
    fgets (input, sizeof (input), stdin);
    input[strlen(input) - 1] = '\0';
    char ** arguments = parse_args(input);
    if(strcmp(arguments[0], "command") == 0){
      printf("Enter 'help' for command details or type your own command: ");
      fgets (commands, sizeof(commands), stdin);
      commands[strlen(commands) - 1] = '\0';
      char ** args2 = parse_args(commands);
      executeCommand(args2, 1, server_board, client_board, pointer1, pointer2);
      free(arguments);
      free(args2);
    }
    else if (strcmp(arguments[0], "attack") == 0){
      printf ("Type in your coordinates: ");
      fgets (commands, sizeof(commands), stdin);
      cords = parse_args (commands);
      free(arguments);
      break;
    }
    else{
      printf("Invalid inputs. Try again :(\n");
    }
  }

    // Send attack (VIA COORS)
    cor = malloc(sizeof(cor));
    cor->x = atoi (cords[0]);
    r = atoi (cords[0]);
    cor->y = atoi (cords[1]);
    c = atoi (cords[1]);
    send(client_socket, cor, sizeof(cor), 0);
    free(cor);

    // Get response (CHECKS if won)
    s_msg = malloc(sizeof(s_msg));
    recv(client_socket, s_msg, sizeof(s_msg), 0);

    switch (s_msg->response)
    // This is where we find out if the coordinates hit a ship
    { // CLIENT BLANK BOARD
        case 0: // A miss so nothing happens
            pointer2->board[r][c] = 3; //Change the status
            break;
        case 1: // A hit
            pointer2->board[r][c] = 2; //Change the status
            break;
        case 3: //A win
            system("clear");
            printf("\nYOU WON!!!\n\n");
            printf("Where do you want to export the history file?\nEnter . to leave it here:");
            char stuff[1000];
            fgets(stuff,sizeof(stuff), stdin);
            char ** argy = parse_args(stuff);
            exportHistory(argy[0]);
            close(client_socket);
            exit(1);
        default:
            break;
    }
    free(s_msg);

    system("clear");

// Client attacks -----------------------------------------------------

    printf("DISPLAYING MY BOARD\n");
    display_my_board(server_board);
    printf("\n");
    printf("DISPLAYING THEIR BOARD\n");
    display_my_board(client_board);
    // Receive attack
    printf("Waiting for an attack\n");
    cor = malloc(sizeof(cor));
    recv(client_socket, cor, sizeof(cor), 0);

    // Send response
    s_msg = malloc(sizeof(s_msg));
    s_msg->type = 3;

    if (attack(cor->x, cor->y, 2, pointer1, pointer2) == 1) // if hit
    {
        if (finished(pointer1) == 0) // Check for win conditions here
        {
            s_msg->response = 3; // This means lost
            send(client_socket, s_msg, sizeof(s_msg), 0);
            free(cor);
            free(s_msg);
            system("clear");
            printf("\nYOU LOST!!!\n\n");
            printf("Where do you want to export the history file?\nEnter . to leave it here:");
            char stuff[1000];
            fgets(stuff,sizeof(stuff), stdin);
            char ** argy = parse_args(stuff);
            exportHistory(argy[0]);
            close(client_socket);
            exit(1);
        }
        else // It was just a hit
        {
            s_msg->response = 1;
        }
    }
    else { // This means it was a miss
        s_msg->response = 0;
    }
    send(client_socket, s_msg, sizeof(s_msg), 0);
    free(cor);
    free(s_msg);
    system("clear");
}
system("clear");

}
