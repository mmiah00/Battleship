#include "networking.h"
#include "battleship.c"


struct gameBoard server_board;
struct gameBoard client_board;


int main(int argc, char **argv) {

  // Messages settings
  struct status_message *s_msg;
  struct coordinate *cor;

// The sockets
  int server_socket;

// commands and boards
  char commands[BUFFER_SIZE];
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

  if (argc == 2)
    server_socket = client_setup(argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  printf ("Let's place your ships!\n\n");
  placingShips (client_board, 2, 1);
  printf("\nShips ready!\n");
  // ------------------------------------------------------------------------

  s_msg = malloc(sizeof(s_msg));
  s_msg->type = 3;
  s_msg->response = 2;
  send(server_socket, s_msg, sizeof(s_msg), 0);
  free(s_msg);


  // ------------------------------------------------------------------------
    // Game starts

while(1)
    {
        // Server attacks -----------------------------------------------------
        int r, c;
        display ("ally", client_board.player, client_board, server_board);


        // Receive attack
        printf("Waiting for an attack\n");
        //CAN put executeCommand
        cor = malloc(sizeof(cor));
        recv(server_socket, cor, sizeof(cor), 0);

        // Send response
        s_msg = malloc(sizeof(s_msg));
        s_msg->type = 3;
        // SERVER ATTACKS
        if (attack(cor->x, cor->y, 1 , pointer1, pointer2) == 1) // if hit
        {
            if (finished(pointer2) == 0) // Check for win conditions here
            {
                s_msg->response = 3; // This means lost
                send(server_socket, s_msg, sizeof(s_msg), 0);
                free(cor);
                free(s_msg);
                system("clear");
                printf("\nYOU LOST!!!\n\n");
                close(server_socket);
                exit(1);
            }
            else
            {
                s_msg->response = 1; // This means hit
            }
        }
        else {
            s_msg->response = 0; // This means miss
        }

        send(server_socket, s_msg, sizeof(s_msg), 0); //send to the server
        free(cor);
        free(s_msg);



// Your turn to attack ------------------------------------------------

    display("ally", client_board.player, client_board, server_board);


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
        send(server_socket, cor, sizeof(cor), 0);
        free(cor);

        // Get response (CHECKS if won)
        s_msg = malloc(sizeof(s_msg));
        recv(server_socket, s_msg, sizeof(s_msg), 0);

        switch (s_msg->response)
        // This is where we find out if the coordinates hit a ship
        {
            case 0: // A miss so nothing happens
                pointer1->board[r][c] = 3;
                break;
            case 1: // A hit
                pointer1->board[r][c] = 2;
                break;
            case 3: //A win
                system("clear");
                printf("\nYOU WON!!!\n\n");
                close(server_socket);
                exit(1);
            default:
                break;
        }
        free(s_msg);

        system("clear");
    }

    close(server_socket);

    return 0;

}
