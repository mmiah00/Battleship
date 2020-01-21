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
  placingShips (server_board, 2, 1);
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


  // ------------------------------------------------------------------------
  // Game starts
/*  while (1) {

    //select() modifies read_fds
    //we must reset it at each iteration
    FD_ZERO(&read_fds); //0 out fd set
    FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
    FD_SET(listen_socket, &read_fds); //add socket to fd set

    //select will block until either fd is ready
    select(listen_socket + 1, &read_fds, NULL, NULL, NULL);

    //if listen_socket triggered select
    if (FD_ISSET(listen_socket, &read_fds)) {
     client_socket = server_connect(listen_socket);

    }//end listen_socket select
*/
    // ------------------------------------------------------------------------
    // Game starts
while(1) {
    // Server attacks -----------------------------------------------------
    int r, c;
    display ("ally", server_board.player, server_board, client_board);

    char input [1000];                          // printf("x: ");
    printf("Your turn to attack\n");            // scanf("%i", &x);
    printf ("Type in your coordinates: ");      // printf("y: ");
    fgets (input, sizeof (input), stdin);       // scanf("%i", &y);
    char ** cords = parse_args (input);

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
            close(client_socket);
            exit(1);
        default:
            break;
    }
    free(s_msg);

    system("clear");

// Client attacks -----------------------------------------------------

    display("ally", server_board.player, server_board, client_board);

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
}
//}
