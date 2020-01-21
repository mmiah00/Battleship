# Battleship

## Team and Period
Brandon Chen, Maisha Miah, Bryan Monge Serrano Period 4

## Description
This project is a terminal-based version of Battleship the board game. Battleship is a 2 player turn based game with networking serving as the connection. To start, each player place down 5 ships of sizes 2, 3, 3, 4, and 5 on a 8x8 board. After both players placed their ships, they take turns guessing and attacking coordinates where they think an enemy ship is located. Once the other player's fleet has entirely been eliminated, you win. In our project, we used a struct and 2d array to manage the board and ships. ~ represents water, H represents a ship, O represents a successful hit, and X represents a failed hit. When attacking, details will be recorded by writing to the history.txt file. When prompted to display history, the history.txt file will be catted. When the victory conditions are fufilled, players will be prompted to decide where to export their history file to keep as bragging rights.

## Required Libraries

## Instructions
After running make, there will be two primary executables. You could run ./battleship for the version that includes networking. In case networking isn't 100% functional yet so there will be a backup ./nonetworking to demonstrate other gameplay components other than networking. In nonetworking, you place ships as player 1 but attack and win as player 2. Instructions to play the game will be displayed
automatically or displayed when entered 'help'.

## Other information
### Bugs
Exporting isn't quite there yet. When entering '.' or '..' to export history file, it instead gets content copied or renamed to a file called '.'
or '..' as a dot file.
