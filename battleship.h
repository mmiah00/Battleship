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
#include <sys/wait.h>



struct coordinate;

struct gameBoard;

struct status_message;

int finished(struct gameBoard * pointer);

void introscreen ();

char ** parse_args( char * line );

int isValid(int xcoord, int ycoord, int shipSize, char * HorV, int board[8][8] );

int placeShip(int xcoord, int ycoord, int shipType, char * HorV, int board[8][8], struct gameBoard * pointer);

int attack(int xcoord, int ycoord, int currentPlayer,struct gameBoard * p1Board, struct gameBoard * p2Board);
int display(char * status, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board);
int displayHistory();

void exportHistory(char * path);



int executeCommand(char ** command, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board, struct gameBoard *pointer1, struct gameBoard * pointer2);


void display_my_board (struct gameBoard g);
