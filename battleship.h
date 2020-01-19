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

void introscreen ();

struct gameBoard;

struct coordinate;


int isValid(int xcoord, int ycoord, int shipSize, char * HorV, int board[8][8] );
int placeShip(int xcoord, int ycoord, int shipType, char * HorV, int board[8][8]);

int display(char * status, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board);

int attack(int xcoord, int ycoord, int currentPlayer,int p1Board[8][8],int p2Board[8][8]);

int executeCommand(char ** command, int currentPlayer, struct gameBoard p1Board, struct gameBoard p2Board);

char ** parse_args( char * line );
