#include "battleship.h"
#include "networking.h"

// This is the track decider between the programs (Server (Player 1) or Client (Player 2))
// You should grab the IP Address of the computer and store it like where we want to run them
// Ask the chat which are the ones we want to get or how to get the IP Addresses
int main(){
  introscreen();
  char input[1000];
  while (1){
    printf("Do you want to connect (type: client) or start a game (type: server)? ");
    fgets(input,sizeof(input), stdin);
    input[strlen(input) - 1] = '\0';
    char ** args = parse_args(input);
    printf("recieved: %s\n", input);

    if (strcmp(args[0], "client") == 0){ // This is where the client goes
      printf("Client successful\n");
      char *program[] = {"./client", NULL};
      execvp(program[0],program);// trying to executeCommand
    }
    else if (strcmp(args[0], "server") == 0){ //This is where the Server goes
      printf("Server successful\n");
      char *program2[] = {"./server", NULL};
      execvp(program2[0],program2);
    }
    else{
      printf("Please type server or client. Try again :(\n");
    }
  }
}
