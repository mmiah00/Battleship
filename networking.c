#include "networking.h"

void error_check( int i, char *s ) {
  if ( i < 0 ) {
    printf("[%s] error %d: %s\n", s, errno, strerror(errno) );
    exit(1);
  }
}

/*=========================
  server_setup
  args:

  creates, binds a server side socket
  and sets it to the listening state

  returns the socket descriptor
  =========================*/
int server_setup() {
  int sd, i;

  //create the socket
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  error_check( sd, "server socket" );
  printf("[server] socket created\n");

  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  //IPv4 address
  hints->ai_socktype = SOCK_STREAM;  //TCP socket
  hints->ai_flags = AI_PASSIVE;  //Use all valid addresses
  getaddrinfo(NULL, PORT, hints, &results); //NULL means use local address

  //bind the socket to address and port
  i = bind( sd, results->ai_addr, results->ai_addrlen );
  error_check( i, "server bind" );
  printf("[server] socket bound\n");

  //set socket to listen state
  i = listen(sd, 10);
  error_check( i, "server listen" );
  printf("[server] socket in listen state\n");

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  return sd;
  // socket listening
}


/*=========================
  server_connect
  args: int sd

  sd should refer to a socket in the listening state
  run the accept call

  returns the socket descriptor for the new socket connected
  to the client.
  =========================*/
int server_connect(int sd) {
  int client_socket;
  socklen_t sock_size;
  struct sockaddr_storage client_address;

  sock_size = sizeof(client_address);
  client_socket = accept(sd, (struct sockaddr *)&client_address, &sock_size);
  error_check(client_socket, "server accept");
  printf ("You are connected\n\n");

  return client_socket;
}

/*=========================
  client_setup
  args: int * to_server

  to_server is a string representing the server address

  create and connect a socket to a server socket that is
  in the listening state

  returns the file descriptor for the socket
  =========================*/
int client_setup(char * server) {
  int sd, i;

  //create the socket
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  error_check( sd, "client socket" );

  //run getaddrinfo
  /* hints->ai_flags not needed because the client
     specifies the desired address. */
  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  //IPv4
  hints->ai_socktype = SOCK_STREAM;  //TCP socket
  getaddrinfo(server, PORT, hints, &results);

  //connect to the server
  //connect will bind the socket for us
  i = connect( sd, results->ai_addr, results->ai_addrlen );
  error_check( i, "client connect" );
  printf ("You are connected\n\n");

  free(hints);
  freeaddrinfo(results);

  return sd;
}

void read_write(int client_socket, struct gameBoard *server, struct gameBoard *client) {// This is for the server to process information
  char buffer[BUFFER_SIZE];

  while (1) {
    printf("Enter coordinates: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    //This is what is sent
    // MAKE SERVER GO FIRST THEN ALLOW CLIENT TO GO
    write(client_socket, buffer, sizeof(buffer));
    read(client_socket, buffer, sizeof(buffer));

    // char ** coords = parse_args (buffer);
    // int x = atoi (coords[0]);
    // int y = atoi (coords[1]);
    // attack (x,y, 1, server, client);

    // This is where you would process information
//    printf("[server] received: [%s]\n", buffer);
  }
  close(client_socket);

  exit(0);


}
