#include "networking.h"

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

int main(int argc, char **argv) {
  int server_socket;
  char buffer[BUFFER_SIZE];
  i = 0;
  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));

    struct coordinate c = makecor (buffer);
    addcor (c);

    printf("received: [%s]\n", buffer);
  }
}
