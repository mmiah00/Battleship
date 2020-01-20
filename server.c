#include "networking.h"
#include "battleship.c"

struct gameBoard server_board;
struct gameBoard client_board;

int main() {

  int listen_socket;
  int client_socket;
  server_board.player = 1;
  client_board.player = 2;

  char buffer[BUFFER_SIZE];

  //set of file descriptors to read from
  fd_set read_fds;

  listen_socket = server_setup();

  //setting up your own board before it connects 
  printf ("Let's place your ships!\n\n");
  placingShips (server_board, 2, 1);
  printf ("Waiting for other player... \n");

  while (1) {

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

    read_write(client_socket, &server_board, &client_board);
}}
