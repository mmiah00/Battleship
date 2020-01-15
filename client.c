#include "networking.h"
#include "main.c"

struct coordinate {
  int x,y;
};

struct coordinate spots_hit [100]; //coordinates you have attacked on the other team
int i; //to keep track of the index of spots_hit

struct coordinate makecor (char *str) {
  struct coordinate cor;
  char * dup = strdup (str);
  int i = 0;
  while (i < 2) {
    str = strsep (&dup, " ");
    if (i == 0) {
      cor.x = atoi (str);
    }
    else {
      cor.y = atoi (str);
    }
    i ++;
  }
  return cor;
}

void addcor (struct coordinate c) {
  spots_hit[i] = c;
  i ++;
}

void initialize (struct gameBoard g) {
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      g.board[r][c] = 0;//0 represents water, -1 represents a ship, 1 represents a hit, 2 represents a miss
    }
  }
}

int main(int argc, char **argv) {
  int server_socket;
  i = 0;
  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  struct gameBoard board;
  struct gameBoard board2;
  initialize (board); initialize (board2); 

  while (1) {
    char buffer[BUFFER_SIZE];
    printf("Enter coordinates: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));

    struct coordinate c = makecor (buffer);
    addcor (c);
    printf ("Added: {%d, %d}\n", spots_hit[i-1].x, spots_hit[i-1].y);

    char size[BUFFER_SIZE];
    printf("How long do you want your ship? ");
    fgets(size, sizeof(size), stdin);
    *strchr(size, '\n') = 0;
    write(server_socket, size, sizeof(size));
    read(server_socket, size, sizeof(size));

    char direction[BUFFER_SIZE];
    printf("Horizontal or vertical? ");
    fgets(direction, sizeof(direction), stdin);
    *strchr(direction, '\n') = 0;
    write(server_socket, direction, sizeof(direction));
    read(server_socket, direction, sizeof(direction));

    placeShip (c.x, c.y, atoi (size), direction, board.board);
    display ("ally", 1, board, board2);

    printf("received: [{%d,%d}, %s, %s]\n", c.x, c.y, direction, size);
  }
}
