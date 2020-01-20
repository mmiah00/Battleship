#include "networking.h"
#include "battleship.c"

struct gameBoard client_board;
struct gameBoard server_board;

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];
  char commands[BUFFER_SIZE];
  client_board.player = 2;
  server_board.player = 1;

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  printf ("Let's place your ships!\n\n");
  placingShips (client_board, 2, 1);
  printf ("Waiting for other player... \n");

  int gameFinished = 0; //0 means not finished
  int running = 1;
  while (running) {
    printf("Awaiting your next command. Type HELP, HISTORY, DISPLAY, or ATTACK: ");
    fgets(commands, sizeof(commands), stdin);
    *strchr(commands, '\n') = 0;
    //write(server_socket, commands, sizeof(commands));
    char ** args = parse_args (commands);
    if (strcmp (args[0], "exit") == 0) {
      running = 0;
      return 0;
    }
    else {
      if (strcmp (args[0], "attack") == 0) {
        printf ("Type in coordinates: ");
        fgets (buffer, sizeof (buffer), stdin);
        *strchr (buffer, '\n') = 0;
        write (server_socket, buffer, sizeof (buffer));
        read (server_socket, buffer, sizeof(buffer));
        char ** coords = parse_args (buffer);
        int x = atoi (coords[0]);
        int y = atoi (coords[1]);
        attack (x,y, client_board.player, &client_board, &server_board);
      }
      else {
        executeCommand (args, client_board.player, client_board, server_board);
      }
    }
    //Goes Second
    read(server_socket, buffer, sizeof(buffer));

    // This is where they process info and add it to the invisible board
    // Maisha this is where we would have the gameplay lol

//    printf("received: [%s]\n", buffer);
//    printf("[client] received: [%s]\n", buffer);
  }
}
